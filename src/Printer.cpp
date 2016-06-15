/*
 * Printer.cpp
 *
 *  Created on: May 12, 2016
 *      Author: guille
 */

#include "Printer.h"

Printer::Printer(SymbolTable *_symbolTable, string outputName) {

	nameFile = outputName.substr(0, outputName.length() - 2) + ".json";

	outputFlow.open(nameFile);
	symbolTable = _symbolTable;
	printFile = true;

	cout << "Creating " << nameFile << " file" << endl;
}

void Printer::dontGenerateFile() {

	printFile = false;
}

void Printer::printGates(int i) {

	for (int j = 0; j < VECTORMAXSIZE; j++) {

		if (symbolTable->getSymbolByBitPosition(i, j) != NOVALUE
				&& symbolTable->getSymbolByBitPosition(i, j)
						!= TYPESCXTO) {

			outputFlow << "{" << endl << "\"position\":" << j << "," << endl
					<< "\"name\": \""
					<< symbolTable->whichSymbol(
							(symbolTable->getSymbolByBitPosition(i, j)))
					<< "\"";

			printSpecialCaseCX(i,j);

			outputFlow << endl << "}" << endl;
			printCommaIfNotLastValue(j, symbolTable->getPositionByBit(i));
		}
	}
}

void Printer::printSpecialCaseCX(int i, int j) {

	if (symbolTable->getSymbolByBitPosition(i, j) == TYPESCXFROM) {

		outputFlow << "," << endl << "\"to\": ";

		if (i > 0
				&& symbolTable->getSymbolByBitPosition(i - 1, j)
						== TYPESCXTO) {
			outputFlow << i - 1;
		}

		else {

			outputFlow << i + 1;
		}
	}
}

void Printer::print() {

	outputFlow << "{" << endl << "\"jsonQasm\": {" << endl
			<< "\"playground\": [" << endl;

	printPlayground();

	outputFlow << "]," << endl;

	printEndFile();
}

void Printer::printEndFile() {

	outputFlow << "\"numberColumns\":" << VECTORMAXSIZE << ","
			<< endl << "\"numberLines\":" << NUMBEROFBITS << ","
			<< endl << "\"numberGates\":" << symbolTable->getNumberOfGates()
			<< "," << endl << "\"hasMeasures\":" << "true" << endl << "}}";
}

void Printer::printCommaIfNotLastValue(short value1, short value2) {

	if (value1 != (value2 - 1)) {

		outputFlow << ",";
	}
}

void Printer::printPlayground() {

	for (int i = 0; i < NUMBEROFBITS; i++) {

		outputFlow << "{" << endl << "\"line\": " << i << "," << endl
				<< "\"name\": \"q\"," << endl << "\"gates\": [";

		printGates(i);

		outputFlow << "]" << endl << "}";

		printCommaIfNotLastValue(i, NUMBEROFBITS);
	}
}

Printer::~Printer() {

	outputFlow.close();
	if (!printFile) {

		if (remove(nameFile.c_str()) != 0) {

			cout << "Error deleting file" << endl;
		} else {

			cout << "File deleted" << endl;
		}
	}
}
