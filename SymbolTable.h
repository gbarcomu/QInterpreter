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

	short q0[constants::VECTORMAXSIZE];
	short q1[constants::VECTORMAXSIZE];
	short q2[constants::VECTORMAXSIZE];
	short q3[constants::VECTORMAXSIZE];
	short q4[constants::VECTORMAXSIZE];

	short nextPosition[constants::NUMBEROFBITS];
	bool bitsInitialized[constants::NUMBEROFBITS];
	short numberOfGates;

	bool anyMeasure;
	bool anyBloch;

	void init();
	void printSymbolTable();
	void updatePositionAndInitialized(short bit);

public:
	SymbolTable();
	~SymbolTable();

	short insertSymbol(short bit, short position, short symbol);
	short getSymbolByBitPosition(short bit, short position);
	short getPositionByBit(short bit);
	short setPositionByBit(short bit, short newPosition);
	short isBitInitialized(short bit);
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
