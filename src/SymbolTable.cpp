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

	for (int i = 0; i < NUMBEROFBITS; i++) {

		lastPositionTakenUp[i] = 0;
		bitsState[i] = BITSTATENOINITIALIZED;
		bitsSelected[i] = false;
	}

	for (int i = 0; i < VECTORMAXSIZE * NUMBEROFBITS; i++) {

		qVector[i] = NOVALUE;
	}
}

short SymbolTable::getSymbolByBitPosition(short bit, short position) {

	short response = NOTFOUND;

	if (position >= 0 && position < VECTORMAXSIZE) {

		response = qVector[bit * VECTORMAXSIZE + position];
	}

	return response;
}

short SymbolTable::insertSymbol(short bit, short position, short symbol) {

	short response = OK;

	if (position >= 0 && position < VECTORMAXSIZE) {

		if (bitsState[bit] != BITSTATECLOSED) {

			qVector[bit * VECTORMAXSIZE + position] = symbol;
			updatePositionAndInitialized(bit);
		}

		else {

			response = ERRORNOGATESAFTERMEASURES;
		}
	}

	else {

		response = ERROROUTOFBOUNDS;
	}

	return response;
}

short SymbolTable::getPositionByBit(short bit) {

	return lastPositionTakenUp[bit];
}

void SymbolTable::updatePositionAndInitialized(short bit) {

	bitsState[bit] = BITSTATEOPEN;
	lastPositionTakenUp[bit]++;

}

void SymbolTable::setPositionByBit(short bit, short newPosition) {

	lastPositionTakenUp[bit] = newPosition;
}

SymbolTable::~SymbolTable() {

//	printSymbolTable();
}

void SymbolTable::printSymbolTable() {

	for (int i = 0; i < NUMBEROFBITS; i++) {

		cout << "q" << i << " : ";

		printBitLine(i * VECTORMAXSIZE, i * VECTORMAXSIZE + lastPositionTakenUp[i]);

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

	if (bitsState[bit] == BITSTATENOINITIALIZED) {

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

	bitsState[bit] = BITSTATECLOSED;
}

string SymbolTable::whichSymbol(short symbol) {

	string response = "-";

	switch (symbol) {

	case TYPEX:
		response = "x";
		break;
	case TYPEY:
		response = "y";
		break;
	case TYPEZ:
		response = "z";
		break;
	case TYPEID:
		response = "id";
		break;
	case TYPEH:
		response = "h";
		break;
	case TYPES:
		response = "s";
		break;
	case TYPET:
		response = "t";
		break;
	case TYPETDG:
		response = "tdg";
		break;
	case TYPESDG:
		response = "sdg";
		break;
	case TYPEMEASURE:
		response = "measure";
		break;
	case TYPEBLOCH:
		response = "bloch";
		break;
	case TYPESCXFROM:
		response = "cx";
		break;
	}

	return response;
}

void SymbolTable::cleanBitSelected() {

	for (int i = 0; i < NUMBEROFBITS; i++) {

		bitsSelected[i] = false;
	}
}
