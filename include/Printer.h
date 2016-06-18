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
#include "QuantumAPIService.h"

class Printer {

private:

	SymbolTable *symbolTable;
	ofstream outputFlow;

	bool printFile;
	string nameFile;

	void printGates(int i);
	void printPlayground();
	void printEndFile();
	bool printCommaIfNotLastValue(short value1, short value2);
	void printCommaIfGateClosed(short bit);
	void printSpecialCaseCX(int i, int j);
	void printFillWithEmptyDoors(int i);

public:
	Printer(SymbolTable *_symbolTable, string outputName);

	void dontGenerateFile();

	void print();

	~Printer();
};

#endif /* PRINTER_H_ */
