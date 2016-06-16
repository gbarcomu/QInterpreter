%{
#include "Parser.h"
#include <math.h>
int n_lines;
%}

%option noyywrap

%x COM

DIGIT [0-9]

%%

"//"					BEGIN(COM);
<COM>"\n"				BEGIN(0); n_lines++;

<COM>.					;

"x"						return X;
"y"						return Y;
"z"						return Z;
"id"					return ID;
"h"						return H;
"s"						return S;
"t"						return T;
"tdg"					return TDG;
"sdg"					return SDG;
"cx"					return CX;
"measure"				return MEASURE;
"bloch"					return BLOCH;

"wait"					return WAIT;

\n					    n_lines++;

{DIGIT}+				yylval.value = atoi(yytext); return NUMBER;

[\t\r ]					;	

. 						return (yytext[0]);

%%
