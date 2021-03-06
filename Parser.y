
%{
#include "Printer.h"
#include "SymbolTable.h"
#include "ErrorController.h"
#include <iostream>
#include <cmath>
#include <list>
	
using namespace std;
     			
extern int n_lines;
extern int yylex();
extern FILE *yyin;

// Store variables with its values and all the necessary information
SymbolTable *symbolTable;
// Manages semantic errors
ErrorController *errorController;
// Create json file
Printer *printer;

/*CX case have two values, the solution is keep these values in the list as - (firstValue*10 + secondValue) to be distinguished of the others */
list <short> loopInstructions;

bool inLoop;
short loopTimes;

void yyerror(const char* s){

    cout << "Syntax error in line "<< n_lines << endl;
    printer->dontGenerateFile();
} 

void equalizePositionsToTheHighest(short bitFrom, short bitTo) {
	
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

void insertMultipleSymbols(short symbol) {
	
	for (int i = 0; i < NUMBEROFBITS; i++) {
		
		if (symbolTable->getBitSelected(i)) {
			
			insertSymbol(i,symbol);
		}
	}	
}

void blockMultipleBitLane() {
	
	for (int i = 0; i < NUMBEROFBITS; i++) {
		
		if (symbolTable->getBitSelected(i)) {
			
			symbolTable->blockBitLine(i);
		}
	}	
}

// Used for CX symbol
void insertDoubleSymbol(short bitFrom, short bitTo) {
	
	equalizePositionsToTheHighest(bitFrom,bitTo);
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

void doLoop() {
	
	for (int i = 0; i < loopTimes; i++) { 
		
		for (std::list <short>::iterator it=loopInstructions.begin(); it != loopInstructions.end(); ++it) {
			
			short _short = (short)*it; 

			// CX case
			if (_short < 0) {
				
				_short = -_short;
				
				insertDoubleSymbol(_short/10,_short%10);
			}
			
			else {
				
				insertMultipleSymbols(_short);

			}
		}	
}
	
	symbolTable->cleanBitSelected();
	inLoop = false;
	loopTimes = 1;
	loopInstructions.clear();
}

void storeInstruction(short instruction) {
	
	loopInstructions.push_back(instruction);
}

%}

%union{

  short value;
} 

%start QuantumProgram // Starting symbol

// Tokens
%token CX REPEAT
%token <value> Y Z ID S T TDG SDG X H
%token <value> MEASURE BLOCH
%token <value> NUMBER
%type <value> typeOfGate

%%

QuantumProgram
	: lines
	;



lines
	: 
	| lines line
	;

line: CX 				'q' '[' NUMBER ']' ',' 'q' '[' NUMBER ']' ';' { if (inLoop) {storeInstruction(-($9*10+$4));} else {insertDoubleSymbol($9, $4);} }
	| typeOfGate 		'q' '[' multiple ']' ';' { if (inLoop) {storeInstruction($1);} else {insertMultipleSymbols($1); symbolTable->cleanBitSelected();}}
	| MEASURE 	    	'q' '[' multiple ']' ';' { insertMultipleSymbols($1); symbolTable->setAnyMeasure(true); blockMultipleBitLane(); symbolTable->cleanBitSelected();}
	| BLOCH   		 	'q' '[' multiple ']' ';' { insertMultipleSymbols($1); symbolTable->setAnyBloch(true); blockMultipleBitLane(); symbolTable->cleanBitSelected();}
	| loop
	;

typeOfGate: X {$$ = $1;}		
	| Y 	  {$$ = $1;}		
	| Z       {$$ = $1;}		
	| ID 	  {$$ = $1;}		
	| H 	  {$$ = $1;}	
	| S       {$$ = $1;}		
	| T 	  {$$ = $1;}	
	| TDG 	  {$$ = $1;}	
	| SDG 	  {$$ = $1;}	
	;
	
multiple: NUMBER 			{ symbolTable->setBitSelected($1); }
	| multiple ',' NUMBER	{ symbolTable->setBitSelected($3); }
	;
	
loop: _repeat times '{' lines '}' { doLoop(); }
	;

_repeat: REPEAT				{ inLoop = true; }
	;


times: NUMBER {loopTimes = $1;}
	;

%%

// It's necessary to introduce a file route as a parameter with .q extension
int main(int argc,char *argv[]){
    
	if (argv[1] == NULL) {
		
		cout << "Error, no parameters found" << endl;
		return 0;
	}
	
     n_lines = 0;
     inLoop = false;
     loopTimes = 1;
     
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