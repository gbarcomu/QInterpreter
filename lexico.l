%{
#include "expresiones.h"
#include <math.h>
int n_lineas;
%}

%option noyywrap

%x COM

%%

"//"					BEGIN(COM);
<COM>"\n"				BEGIN(0); n_lineas++;

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

\n					    n_lineas++;
[0-9]+					yylval.value = atoi(yytext);return NUMBER;
[\t ]					;	
. 						return (yytext[0]);
%%
