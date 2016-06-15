/*
 * Printer.h
 *
 *  Created on: May 12, 2016
 *      Author: guille
 */

#ifndef PRINTER_H_
#define PRINTER_H_

#include "Constants.h"
#include <fstream>
#include <sstream>
#include "SymbolTable.h"

class Printer {

private:

	SymbolTable *symbolTable;
	ofstream outputFlow;

	bool printFile;
	string nameFile;

	void printGates(int i);
	void printPlayground();
	void printEndFile();
	void printCommaIfNotLastValue(short value1, short value2);
	void printSpecialCaseCX(int i, int j);

public:
	Printer(SymbolTable *_symbolTable, string outputName);

	void dontGenerateFile();

	void print();

	~Printer();
};

#endif /* PRINTER_H_ */
