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

//	cout << "Creating " << nameFile << " file" << endl;
}

void Printer::dontGenerateFile() {

	printFile = false;
}

void Printer::printGates(int i) {

	for (int j = 0; j < VECTORMAXSIZE; j++) {

		if (symbolTable->getSymbolByBitPosition(i, j) != NOVALUE
				&& symbolTable->getSymbolByBitPosition(i, j) != TYPESCXTO) {

			outputFlow << "{" << "\"position\":" << j << "," << "\"name\": \""
					<< symbolTable->whichSymbol(
							(symbolTable->getSymbolByBitPosition(i, j)))
					<< "\"";

			printSpecialCaseCX(i, j);

			outputFlow << "}";
			if (printCommaIfNotLastValue(j, symbolTable->getPositionByBit(i))) {

				printCommaIfGateClosed(i);
			}
		}
	}
}

void Printer::printSpecialCaseCX(int i, int j) {

	if (symbolTable->getSymbolByBitPosition(i, j) == TYPESCXFROM) {

		outputFlow << "," << "\"to\": ";

		for (int k = 0; k < NUMBEROFBITS; k++) {

			if (i > 0 && symbolTable->getSymbolByBitPosition(k, j)
			== TYPESCXTO) {
				outputFlow << k;
			}
		}
	}
}

void Printer::print() {

	outputFlow << "{" << "\"jsonQasm\": {" << "\"playground\": [";

	printPlayground();

	outputFlow << "],";

	printEndFile();
}

void Printer::printEndFile() {

	outputFlow << "\"numberColumns\":" << VECTORMAXSIZE << ","
			<< "\"numberLines\":" << NUMBEROFBITS << "," << "\"numberGates\":"
			<< symbolTable->getNumberOfGates() << "," << "\"hasMeasures\":"
			<< "true," << "\"topology\":\"250e969c6b9e68aa2a045ffbceb3ac33\""
			<< "}}";
}

bool Printer::printCommaIfNotLastValue(short value1, short value2) {

	if (value1 != (value2 - 1)) {

		outputFlow << ",";
		return false;
	}

	return true;
}

void Printer::printCommaIfGateClosed(short bit) {

	if (symbolTable->getBitState(bit) == BITSTATECLOSED) {

		outputFlow << ",";
	}
}

void Printer::printPlayground() {

	for (int i = 0; i < NUMBEROFBITS; i++) {

		outputFlow << "{" << "\"line\": " << i << "," << "\"name\": \"q\","
				<< "\"gates\": [";

		printGates(i);
		printFillWithEmptyDoors(i);

		outputFlow << "]" << "}";

		printCommaIfNotLastValue(i, NUMBEROFBITS);
	}
}

void Printer::printFillWithEmptyDoors(int i) {

	if (symbolTable->getBitState(i) == BITSTATECLOSED) {

		for (int j = symbolTable->getPositionByBit(i); j < VECTORMAXSIZE; j++) {

			outputFlow << "{ \"position\":" << j << "}";
			symbolTable->increseInOneNumberOfGates();
			printCommaIfNotLastValue(j, VECTORMAXSIZE);
		}
	}
}

Printer::~Printer() {

	outputFlow.close();
	if (!printFile) {

		if (remove(nameFile.c_str()) != 0) {

			cout << "Error deleting file";
		} 
	}

	else {

		QuantumAPIService *quantumAPIService = new QuantumAPIService(nameFile);

		quantumAPIService->sendJsonFileToTheAPI();

		delete quantumAPIService;
	}
}
