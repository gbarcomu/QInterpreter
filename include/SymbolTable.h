/*
 * SymbolTable.h
 *
 *  Created on: Apr 14, 2016
 *      Author: guille
 */

#ifndef SYMBOLTABLE_H_
#define SYMBOLTABLE_H_

#include <sstream>
#include "Constants.h"

using std::string;

namespace qi 
{

class SymbolTable {

private:

	short qVector[VECTORMAXSIZE * NUMBEROFBITS];

	short lastPositionTakenUp[NUMBEROFBITS];
	short bitsState[NUMBEROFBITS];

	bool bitsSelected[NUMBEROFBITS];

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

	void cleanBitSelected();

	/*
	 * Return the last position occupied in a bit line
	 */
	short getPositionByBit(short bit);

	/*
	 * Return the last position occupied in a bit line excluding TYPESCXTO
	 */
	short getPositionByBitExcludingCXTO(short bit);

	/*
	 * In case of gates that uses more than one bit, it is necessary to update
	 * the last position occupied of each bit to the highest value
	 */
	void setPositionByBit(short bit, short newPosition);
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

	short getBitState(int bit) const {
		return bitsState[bit];
	}

	bool getBitSelected(int bit) const {
		return bitsSelected[bit];
	}

	short setBitSelected(int bit) {
		bitsSelected[bit] = true;return 0;
	}
};

} // namespace qi

#endif /* SYMBOLTABLE_H_ */
