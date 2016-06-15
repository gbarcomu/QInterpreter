
%{

#include <iostream>
#include <cmath>
#include <stack>
#include <list>
#include "SymbolTable.h"
#include "ErrorController.h"
#include "Printer.h"
	
using namespace std;
     			
extern int n_lineas;
extern int yylex();
extern FILE *yyin;


// Store variables with its values and all the necesary information
SymbolTable *symbolTable;
// Manages semantic errors
ErrorController *errorController;
// Create json file
Printer *printer;


void yyerror(const char* s){

    cout << "Syntax error in line "<< n_lineas <<endl;
    printer->dontGenerateFile();
} 

void equalisePositionsToTheHighest(short bitFrom, short bitTo) {
	
	short positionFrom = symbolTable->getPositionByBit(bitFrom);
	short positionTo = symbolTable->getPositionByBit(bitTo);
	if (positionFrom > positionTo) {
		
		symbolTable->setPositionByBit(bitTo, positionFrom);
	}
	else {
		
		symbolTable->setPositionByBit(bitFrom, positionTo);
	}
}

void insertSymbol(short bit, short symbol) {
	
	symbolTable->increseInOneNumberOfGates();
	short position = symbolTable->getPositionByBit(bit);
	short response = symbolTable->insertSymbol(bit,position, symbol);
		
	if (response != OK) {
		
		errorController->errorCatcher(response);
	}
}

/* Used for CX symbol */
void insertDoubleSymbol(short bitFrom, short bitTo) {
	
	equalisePositionsToTheHighest(bitFrom,bitTo);
	symbolTable->increseInOneNumberOfGates();
	
	short position = symbolTable->getPositionByBit(bitFrom);
	short response = symbolTable->insertSymbol(bitFrom,position, TYPESCXFROM);
	
	if (response != OK) {
		
		errorController->errorCatcher(response);
	}
	
	else {
		
		response = symbolTable->insertSymbol(bitTo,position, TYPESCXTO);
		
		if (response != OK) {
			
			errorController->errorCatcher(response);
		}
	}		
}

%}

%union{

  short value;
} 

%start QuantumProgram /* Starting symbol */

/* Tokens */
%token X Y Z ID H S T TDG SDG CX
%token MEASURE BLOCH
%token WAIT
%token<value> NUMBER


%%

QuantumProgram: lines
	;

lines: 
	| lines line
	;

line: CX 'q' '[' NUMBER ']' ',' 'q' '[' NUMBER ']' ';' {insertDoubleSymbol($9, $4);}
	| X 'q' '[' NUMBER ']' ';' {insertSymbol($4,TYPEX);}
	| Y 'q' '[' NUMBER ']' ';' {insertSymbol($4,TYPEY);}
	| Z 'q' '[' NUMBER ']' ';' {insertSymbol($4,TYPEZ);}
	| ID 'q' '[' NUMBER ']' ';' {insertSymbol($4,TYPEID);}
	| H 'q' '[' NUMBER ']' ';' {insertSymbol($4,TYPEH);}
	| S 'q' '[' NUMBER ']' ';' {insertSymbol($4,TYPES);}
	| T 'q' '[' NUMBER ']' ';' {insertSymbol($4,TYPET);}
	| TDG 'q' '[' NUMBER ']' ';' {insertSymbol($4,TYPETDG);}
	| SDG 'q' '[' NUMBER ']' ';' {insertSymbol($4,TYPESDG);}
	| MEASURE 'q' '[' NUMBER ']' ';' {insertSymbol($4,TYPEMEASURE); symbolTable->setAnyMeasure(true); symbolTable->blockBitLine($4);}
	| BLOCH 'q' '[' NUMBER ']' ';' {insertSymbol($4,TYPEBLOCH); symbolTable->setAnyBloch(true); symbolTable->blockBitLine($4);}
	;

%%

/* Is necessary to introduce a file route as a parameter with .q extension*/
int main(int argc,char *argv[]){
    
	if (argv[1] == NULL) {
		
		cout << "Error, no parameters found" << endl;
		return 0;
	}
	
     n_lineas = 0;
     
     symbolTable = new SymbolTable();
     printer = new Printer(symbolTable, argv[1]);
     errorController = new ErrorController(printer);
          
     FILE *inputFile = fopen(argv[1], "r");
         
     yyin = inputFile;
     yyparse();
     
     if (symbolTable->isAnyMeasure() == false && symbolTable->isAnyBloch() == false) {
     
     	errorController->errorCatcher(ERRORNOMEASURES);
     }

     else if (symbolTable->isAnyMeasure() && symbolTable->isAnyBloch()) {
     
     	errorController->errorCatcher(ERRORBLOCHANDMEASURE);
     }     
     
     printer->print();
     
     delete printer;
     delete symbolTable;
     delete errorController;
     
     return 0;
}