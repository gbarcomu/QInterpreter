%{

#include <stdlib.h> // atoi

#include "Parser.h"
#include "Constants.h"

int n_lines;
 
%}
 
%option warn nodefault
%option reentrant noyywrap never-interactive nounistd
%option bison-bridge

%x COM

DIGIT [0-9]

%%

"//"					BEGIN(COM);
<COM>"\n"				BEGIN(0); n_lines++;

<COM>.					;

"x"						yylval->value = TYPEX; return X;
"y"						yylval->value = TYPEY; return Y;
"z"						yylval->value = TYPEZ; return Z;
"id"					yylval->value = TYPEID;return ID;
"h"						yylval->value = TYPEH; return H;
"s"						yylval->value = TYPES; return S;
"t"						yylval->value = TYPET; return T;
"tdg"					yylval->value = TYPETDG; return TDG;
"sdg"					yylval->value = TYPESDG; return SDG;
"cx"					return CX;
"repeat"				return REPEAT;
"measure"				yylval->value = TYPEMEASURE; return MEASURE;
"bloch"					yylval->value = TYPEBLOCH; return BLOCH;

\n					    n_lines++;

{DIGIT}+				yylval->value = atoi(yytext); return NUMBER;

[\t\r ]					;	

. 						return (yytext[0]);

%%
