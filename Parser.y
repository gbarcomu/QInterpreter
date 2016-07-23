%{
#include <iostream>

#include "Expression.h"
#include "Parser.h"
#include "Lexer.h"

using std::cout;
using std::endl;

using namespace qi;

extern int n_lines;

Expression *e = Expression::Instance();

int yyerror(char **fileContent, yyscan_t scanner,const char *msg) {
    fprintf(stderr,"Error:%s\n",msg);
	return 0;
}

%}

%code requires {
 
#ifndef YY_TYPEDEF_YY_SCANNER_T
#define YY_TYPEDEF_YY_SCANNER_T
typedef void* yyscan_t;
#endif
 
}

%define api.pure
%lex-param   { yyscan_t scanner }
%parse-param { char **fileContent }
%parse-param { yyscan_t scanner }
 
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

line: CX 				'q' '[' NUMBER ']' ',' 'q' '[' NUMBER ']' ';' { if (e->inLoop) {e->storeInstruction(-($9*10+$4));} else {e->insertDoubleSymbol($9, $4);} }
	| typeOfGate 		'q' '[' multiple ']' ';' { if (e->inLoop) {Expression::Instance()->storeInstruction($1);} else {e->insertMultipleSymbols($1); e->symbolTable->cleanBitSelected();}}
	| MEASURE 	    	'q' '[' multiple ']' ';' { e->insertMultipleSymbols($1); e->symbolTable->setAnyMeasure(true); e->blockMultipleBitLane(); e->symbolTable->cleanBitSelected();}
	| BLOCH   		 	'q' '[' multiple ']' ';' { e->insertMultipleSymbols($1); e->symbolTable->setAnyBloch(true); e->blockMultipleBitLane(); e->symbolTable->cleanBitSelected();}
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
	
multiple: NUMBER 			{ e->symbolTable->setBitSelected($1); }
	| multiple ',' NUMBER	{ e->symbolTable->setBitSelected($3); }
	;
	
loop: _repeat times '{' lines '}' { e->doLoop(); }
	;

_repeat: REPEAT				{ e->inLoop = true; }
	;


times: NUMBER { e->loopTimes = $1; }
	;

%%

