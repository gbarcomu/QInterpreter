/*
 * SymbolTable.h
 *
 *  Created on: Apr 14, 2016
 *      Author: guille
 */

#ifndef SYMBOLTABLE_H_
#define SYMBOLTABLE_H_

#include <iostream>
#include <map>
#include <unordered_map>
#include <iomanip>
#include <cstring>
#include <sstream>
#include "Constants.h"
using namespace std;

class SymbolTable {

private:

	short qVector[constants::VECTORMAXSIZE * constants::NUMBEROFBITS];

	short lastPositionTakenUp[constants::NUMBEROFBITS];
	short bitsState[constants::NUMBEROFBITS];
	short numberOfGates;

	bool anyMeasure;
	bool anyBloch;

	void init();
	void printSymbolTable();
	void printBitLine(int startPosition, int endPosition);
	void updatePositionAndInitialized(short bit);

public:
	SymbolTable();
	~SymbolTable();

	short insertSymbol(short bit, short position, short symbol);
	short getSymbolByBitPosition(short bit, short position);

	void blockBitLine(short bit);

	/*
	 * Return the last position occupied in a bit line
	 */
	short getPositionByBit(short bit);

	/*
	 * In case of gates that uses more than one bit, it is necessary to update
	 * the last position occupied of each bit to the highest value
	 */
	short setPositionByBit(short bit, short newPosition);
	bool isBitInitialized(short bit);
	short getNumberOfGates();
	void increseInOneNumberOfGates();

	string whichSymbol(short symbol);


/* Auto generated getters and setters */

	bool isAnyBloch() const {
		return anyBloch;
	}

	void setAnyBloch(bool _anyBloch) {
		anyBloch = _anyBloch;
	}

	bool isAnyMeasure() const {
		return anyMeasure;
	}

	void setAnyMeasure(bool _anyMeasure) {
		anyMeasure = _anyMeasure;
	}
};

#endif /* SYMBOLTABLE_H_ */
