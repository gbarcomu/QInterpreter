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

	case ERROROUTOFBOUNDS:
		cout << "Semantic error in line " << n_lines << ", " << "position out of bounds"
				<< endl;
		break;

	case ERRORNOMEASURES:
		cout << "Semantic error, at least one measure gate is needed"
				<< endl;
		break;

	case ERRORBLOCHANDMEASURE:
		cout << "Semantic error, only one type of measure gate is allowed"
				<< endl;
		break;

	case ERRORNOGATESAFTERMEASURES:
		cout << "Semantic error, placing any kind of gates after a measure gate is not allowed"
				<< endl;
		break;
	}
}

ErrorController::~ErrorController() {
}

