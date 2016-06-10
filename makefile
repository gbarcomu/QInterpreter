#fichero Makefile

OBJ = expresiones.o lexico.o SymbolTable.o Printer.o ErrorController.o

all: QInterpreter

QInterpreter : $(OBJ)     
	g++ -oQInterpreter $(OBJ)
	rm -f lex.yy.c expresiones.c expresiones.h

expresiones.o : expresiones.c
	g++ -c  -std=c++11 -oexpresiones.o  expresiones.c
	
SymbolTable.o: SymbolTable.h  SymbolTable.cpp
	g++ -c -std=c++11 -oSymbolTable.o SymbolTable.cpp
	
Printer.o: Printer.h  Printer.cpp
	g++ -c -std=c++11 -oPrinter.o Printer.cpp
	
ErrorController.o: ErrorController.h  ErrorController.cpp
	g++ -c -std=c++11 -oErrorController.o ErrorController.cpp
		
lexico.o : lex.yy.c		
	g++ -c -olexico.o lex.yy.c 	

expresiones.c : expresiones.y     
	bison -d -oexpresiones.c expresiones.y

lex.yy.c: lexico.l
	flex lexico.l

clean : 
	rm  -f *.o lex.yy.c expresiones.c expresiones.h QInterpreter
