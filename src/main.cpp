/*
 * main.c file
 */
#include <string>
#include <iostream>
#include <stdio.h>
#include <cmath>
#include <list>

#include "Expression.h"
#include "Parser.h"
#include "Lexer.h"

using namespace qi;

using std::string;
using std::ifstream;
using std::istreambuf_iterator;
using std::ios;
using std::cout;
using std::endl;

int *getAST( char *fileContent)	// was const char, removed.
{
    yyscan_t scanner;
    YY_BUFFER_STATE state;
 
    if (yylex_init(&scanner)) {
        // couldn't initialize
        return NULL;
    }
 
    state = yy_scan_string(fileContent, scanner);
 
    if (yyparse(&fileContent, scanner)) {
        // error parsing
        return NULL;
    }
 
    yy_delete_buffer(state, scanner);
 
    yylex_destroy(scanner);
 
    //return expression;
	return 0;
}

// It's necessary to introduce a file route as a parameter with .q extension
int main(int argc,char *argv[]){
    
	if (argv[1] == NULL) {
		
		cout << "Error, no parameters found" << endl;
		return 0;
	}
	
     n_lines = 0;

	 // init of Expression
	 //Expression::Instance()->inLoop = false;
	 //Expression::Instance()->loopTimes = 1;  
	 //Expression::Instance()->symbolTable = new SymbolTable();
     Expression::Instance()->printer = new Printer(Expression::Instance()->symbolTable, argv[1]);
     Expression::Instance()->errorController = new ErrorController(Expression::Instance()->printer);
        
	 ifstream fileStream(argv[1]);
	 string fileContent;

	 fileStream.seekg(0, ios::end);   
	 fileContent.reserve(fileStream.tellg());
	 fileStream.seekg(0, ios::beg);

	 fileContent.assign((istreambuf_iterator<char>(fileStream)),
						 istreambuf_iterator<char>());

	 getAST(const_cast<char*>(fileContent.c_str()));
     //yyin = inputFile;
     //yyparse();
     
     if (Expression::Instance()->symbolTable->isAnyMeasure() == false && Expression::Instance()->symbolTable->isAnyBloch() == false) {
     
     	Expression::Instance()->errorController->errorCatcher(ERRORNOMEASURES);
     }

     else if (Expression::Instance()->symbolTable->isAnyMeasure() && Expression::Instance()->symbolTable->isAnyBloch()) {
     
     	Expression::Instance()->errorController->errorCatcher(ERRORBLOCHANDMEASURE);
     }     
     
     Expression::Instance()->printer->print();
     
     delete Expression::Instance()->printer;
     delete Expression::Instance()->symbolTable;
     delete Expression::Instance()->errorController;
     
     return 0;
}