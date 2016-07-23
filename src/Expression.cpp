/*
 * Expression.c
 * Implementation of functions used to build the syntax tree.
 */
#include <iostream>

#include "Expression.h"

using std::cout;

namespace qi
{

Expression * Expression::m_pInstance = NULL;

Expression * Expression::Instance() {
    if (!m_pInstance) {
        m_pInstance = new Expression;
		m_pInstance->inLoop = false;
		m_pInstance->loopTimes = 1;
		m_pInstance->symbolTable = new SymbolTable();

		// TODO implement initialization in a right way, partial init is not an option
		// partially initialization shifted to main.cpp
		//m_pInstance->printer = new Printer(m_pInstance->symbolTable, "BellStateZZMeasurement.q");
		//m_pInstance->errorController = new ErrorController(m_pInstance->printer);
    }
    return m_pInstance;
}

void  Expression::equalizePositionsToTheHighest(short bitFrom, short bitTo) {
	
	short positionFrom = symbolTable->getPositionByBit(bitFrom);
	short positionTo = symbolTable->getPositionByBit(bitTo);
	if (positionFrom > positionTo) {

		symbolTable->setPositionByBit(bitTo, positionFrom);
	}
	else {
		
		symbolTable->setPositionByBit(bitFrom, positionTo);
	}
}

void Expression::insertSymbol(short bit, short symbol) {
	
	symbolTable->increseInOneNumberOfGates();
	short position = symbolTable->getPositionByBit(bit);
	short response = symbolTable->insertSymbol(bit,position, symbol);
		
	if (response != OK) {
		
		errorController->errorCatcher(response);
	}
}

void Expression::insertMultipleSymbols(short symbol) {
	
	for (int i = 0; i < NUMBEROFBITS; i++) {
		
		if ( symbolTable->getBitSelected(i)) {
			
			insertSymbol(i,symbol);
		}
	}	
}

void Expression::blockMultipleBitLane() {
	
	for (int i = 0; i < NUMBEROFBITS; i++) {
		
		if (symbolTable->getBitSelected(i)) {
			
			symbolTable->blockBitLine(i);
		}
	}	
}

// Used for CX symbol
void Expression::insertDoubleSymbol(short bitFrom, short bitTo) {
	
	equalizePositionsToTheHighest(bitFrom,bitTo);
	symbolTable->increseInOneNumberOfGates();
	
	short position = symbolTable->getPositionByBit(bitFrom);
	short response = symbolTable->insertSymbol(bitFrom,position, TYPESCXFROM);
	
	if (response != OK) {
		
		errorController->errorCatcher(response);
	}
	
	else {
		
		response = symbolTable->insertSymbol(bitTo,position, TYPESCXTO);
		
		if (response != OK) {
			
			errorController->errorCatcher(response);
		}
	}		
}

void Expression::doLoop() {
	
	for (int i = 0; i < loopTimes; i++) { 
		
		for (std::list <short>::iterator it=loopInstructions.begin(); it != loopInstructions.end(); ++it) {
			
			short _short = (short)*it; 

			// CX case
			if (_short < 0) {
				
				_short = -_short;
				
				insertDoubleSymbol(_short/10,_short%10);
			}
			
			else {
				
				insertMultipleSymbols(_short);

			}
		}	
	}
	
	symbolTable->cleanBitSelected();
	inLoop = false;
	loopTimes = 1;
	loopInstructions.clear();
}

void Expression::storeInstruction(short instruction) {
	
	loopInstructions.push_back(instruction);
}

} // namespace qi
