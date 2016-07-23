/*
 * Expression.h
 * Definition of the structure used to build the syntax tree.
 */
#ifndef __EXPRESSION_H__
#define __EXPRESSION_H__
 
#include <list>

#include "SymbolTable.h"
#include "ErrorController.h"

extern int n_lines;

using std::list;

namespace qi
{

/**
@ brief
*/
class Expression 
{

public:
	static Expression * Instance();

protected:
	Expression(){}
	
private:
	static Expression * m_pInstance;

public:
	//
	bool inLoop;

	//
	short loopTimes;

	// Store variables with its values and all the necessary information
	SymbolTable *symbolTable;

	// Manages semantic errors
	ErrorController *errorController;

	// Create json file
	Printer *printer;

	// CX case have two values, the solution is keep these values in the list as - (firstValue*10 + secondValue) to be distinguished of the others
	list<short> loopInstructions;

	/**
	* @ brief 
	*/
	void equalizePositionsToTheHighest(short bitFrom, short bitTo);

	/**
	* @ brief 
	*/
	void insertSymbol(short bit, short symbol);

	/**
	* @ brief 
	*/
	void insertMultipleSymbols(short symbol);

	/**
	* @ brief 
	*/
	void blockMultipleBitLane();

	/**
	* @ brief Used for CX symbol
	*/
	void insertDoubleSymbol(short bitFrom, short bitTo);

	/**
	* @ brief 
	*/
	void doLoop();
	
	/**
	* @ brief 
	*/
	void storeInstruction(short instruction);

}; // Expression

} // namespace qi
 
#endif // __EXPRESSION_H__
