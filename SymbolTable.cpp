/*
 * SymbolTable.cpp
 *
 *  Created on: Apr 14, 2016
 *      Author: guille
 */

#include "SymbolTable.h"

SymbolTable::SymbolTable() {

	init();
}

void SymbolTable::init() {

	numberOfGates = 0;
	anyBloch = false;
	anyMeasure = false;

	for (int i = 0; i < constants::NUMBEROFBITS; i++) {

		lastPositionTakenUp[i] = 0;
		bitsState[i] = constants::BITSTATENOINITIALIZED;
	}

	for (int i = 0; i < constants::VECTORMAXSIZE * constants::NUMBEROFBITS; i++) {

		qVector[i] = constants::NOVALUE;
	}
}

short SymbolTable::getSymbolByBitPosition(short bit, short position) {

	short response = constants::NOTFOUND;

	if (position >= 0 && position < constants::VECTORMAXSIZE) {

		response = qVector[bit * constants::VECTORMAXSIZE + position];
	}

	return response;
}

short SymbolTable::insertSymbol(short bit, short position, short symbol) {

	short response = constants::OK;

	if (position >= 0 && position < constants::VECTORMAXSIZE) {

		if (bitsState[bit] != constants::BITSTATECLOSED) {

			qVector[bit * constants::VECTORMAXSIZE + position] = symbol;
			updatePositionAndInitialized(bit);
		}

		else {

			response = constants::ERRORNOGATESAFTERMEASURES;
		}
	}

	else {

		response = constants::ERROROUTOFBOUNDS;
	}

	return response;
}

short SymbolTable::getPositionByBit(short bit) {

	return lastPositionTakenUp[bit];
}

void SymbolTable::updatePositionAndInitialized(short bit) {

	bitsState[bit] = constants::BITSTATEOPEN;
	lastPositionTakenUp[bit]++;

}

short SymbolTable::setPositionByBit(short bit, short newPosition) {

	lastPositionTakenUp[bit] = newPosition;
}

SymbolTable::~SymbolTable() {

	printSymbolTable();
}

void SymbolTable::printSymbolTable() {

	for (int i = 0; i < constants::NUMBEROFBITS; i++) {

		cout << "q" << i << " : ";

		printBitLine(i * constants::VECTORMAXSIZE, i * constants::VECTORMAXSIZE + lastPositionTakenUp[i]);

		cout << endl;
	}
}

void SymbolTable::printBitLine(int startPosition, int endPosition) {

	cout << "Start " << startPosition << ", end " << endPosition << endl;

	for (int i = startPosition; i < endPosition; i++) {

		cout << whichSymbol(qVector[i]) << " ";
	}
}

bool SymbolTable::isBitInitialized(short bit) {

	bool response = true;

	if (bitsState[bit] == constants::BITSTATENOINITIALIZED) {

		response = false;
	}

	return response;
}

short SymbolTable::getNumberOfGates() {

	return numberOfGates;
}

void SymbolTable::increseInOneNumberOfGates() {

	numberOfGates++;
}

void SymbolTable::blockBitLine(short bit) {

	bitsState[bit] = constants::BITSTATECLOSED;
}

string SymbolTable::whichSymbol(short symbol) {

	string response = "-";

	switch (symbol) {

	case constants::TYPEX:
		response = "x";
		break;
	case constants::TYPEY:
		response = "y";
		break;
	case constants::TYPEZ:
		response = "z";
		break;
	case constants::TYPEID:
		response = "id";
		break;
	case constants::TYPEH:
		response = "h";
		break;
	case constants::TYPES:
		response = "s";
		break;
	case constants::TYPET:
		response = "t";
		break;
	case constants::TYPETDG:
		response = "tdg";
		break;
	case constants::TYPESDG:
		response = "sdg";
		break;
	case constants::TYPEMEASURE:
		response = "measure";
		break;
	case constants::TYPEBLOCH:
		response = "bloch";
		break;
	case constants::TYPESCXFROM:
		response = "cx";
		break;
	}

	return response;
}
