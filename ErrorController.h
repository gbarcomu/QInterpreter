/*
 * ErrorController.h
 *
 *  Created on: Apr 20, 2016
 *      Author: guille
 */

#ifndef ERRORCONTROLLER_H_
#define ERRORCONTROLLER_H_

#include<iostream>
#include "Constants.h"
#include "Printer.h"

extern int n_lineas;

using namespace std;

class ErrorController {

private:
	Printer *printer;

public:
	ErrorController(Printer *_printer);

	void errorCatcher(short errorCode,const char *parameter1 = NULL, const char *parameter2 = NULL, const char *parameter3 = NULL);

	~ErrorController();
};

#endif /* ERRORCONTROLLER_H_ */
