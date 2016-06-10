/*
 * ErrorController.cpp
 *
 *  Created on: Apr 20, 2016
 *      Author: guille
 */

#include "ErrorController.h"

ErrorController::ErrorController(Printer *_printer) {

	printer = _printer;
}

void ErrorController::errorCatcher(short errorCode, const char* parameter1,
		const char* parameter2, const char* parameter3) {

	printer->dontGenerateFile();

	switch (errorCode) {

	case constants::ERROROUTOFBOUNDS:
		cout << "Semantic error in line " << n_lineas << ", " << "position out of bounds"
				<< endl;
		break;

	case constants::ERRORNOMEASURES:
		cout << "Semantic error, at least one measure gate is needed"
				<< endl;
		break;

	case constants::ERRORBLOCHANDMEASURE:
		cout << "Semantic error, only one tipe of measure gate is allowed"
				<< endl;
		break;
	}
}

ErrorController::~ErrorController() {
	// TODO Auto-generated destructor stub
}

