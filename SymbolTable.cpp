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

		nextPosition[i] = 0;
		nextPosition[i] = false;
	}

	for (int i = 0; i < constants::VECTORMAXSIZE; i++) {

		q0[i] = constants::NOVALUE;
		q1[i] = constants::NOVALUE;
		q2[i] = constants::NOVALUE;
		q3[i] = constants::NOVALUE;
		q4[i] = constants::NOVALUE;
	}
}

short SymbolTable::getSymbolByBitPosition(short bit, short position) {

	short response = constants::NOTFOUND;

	if (position >= 0 && position < constants::VECTORMAXSIZE) {

		switch (bit) {

		case 0:
			response = q0[position];
			break;
		case 1:
			response = q1[position];
			break;
		case 2:
			response = q2[position];
			break;
		case 3:
			response = q3[position];
			break;
		case 4:
			response = q4[position];
			break;
		}
	}

	return response;
}

short SymbolTable::insertSymbol(short bit, short position, short symbol) {

	short response = constants::ERROROUTOFBOUNDS;

	if (position >= 0 && position < constants::VECTORMAXSIZE) {

		switch (bit) {

		case 0:
			q0[position] = symbol;
			response = constants::OK;
			updatePositionAndInitialized(bit);
			break;
		case 1:
			q1[position] = symbol;
			response = constants::OK;
			updatePositionAndInitialized(bit);
			break;
		case 2:
			q2[position] = symbol;
			response = constants::OK;
			updatePositionAndInitialized(bit);
			break;
		case 3:
			q3[position] = symbol;
			response = constants::OK;
			updatePositionAndInitialized(bit);
			break;
		case 4:
			q4[position] = symbol;
			response = constants::OK;
			updatePositionAndInitialized(bit);
			break;
		}
	}

	return response;
}

short SymbolTable::getPositionByBit(short bit) {

	return nextPosition[bit];
}

void SymbolTable::updatePositionAndInitialized(short bit) {

	bitsInitialized[bit] = true;
	nextPosition[bit]++;

}

short SymbolTable::setPositionByBit(short bit, short newPosition) {

	nextPosition[bit] = newPosition;
}

SymbolTable::~SymbolTable() {

	printSymbolTable();
}

void SymbolTable::printSymbolTable() {

	cout << "q0 : ";

	for (int i = 0; i < nextPosition[0]; i++) {

		cout << whichSymbol(q0[i]) << " ";
	}

	cout << endl;

	cout << "q1 : ";

	for (int i = 0; i < nextPosition[1]; i++) {

		cout << whichSymbol(q1[i]) << " ";
	}

	cout << endl;

	cout << "q2 : ";

	for (int i = 0; i < nextPosition[2]; i++) {

		cout << whichSymbol(q2[i]) << " ";
	}

	cout << endl;

	cout << "q3 : ";

	for (int i = 0; i < nextPosition[3]; i++) {

		cout << whichSymbol(q3[i]) << " ";
	}

	cout << endl;

	cout << "q4 : ";

	for (int i = 0; i < nextPosition[4]; i++) {

		cout << whichSymbol(q4[i]) << " ";
	}

	cout << endl;
}

short SymbolTable::isBitInitialized(short bit) {

	return bitsInitialized[bit];
}

short SymbolTable::getNumberOfGates() {

	return numberOfGates;
}

void SymbolTable::increseInOneNumberOfGates() {

	numberOfGates++;
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
