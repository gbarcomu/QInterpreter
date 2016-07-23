/*
 * ErrorController.h
 *
 *  Created on: Apr 20, 2016
 *      Author: guille
 */

#ifndef ERRORCONTROLLER_H_
#define ERRORCONTROLLER_H_

#include "Constants.h"
#include "Printer.h"

namespace qi
{

class ErrorController {

private:
	Printer *printer;

public:
	ErrorController(Printer *_printer);
	~ErrorController();

	void errorCatcher(short errorCode,const char *parameter1 = NULL, const char *parameter2 = NULL, const char *parameter3 = NULL);
};

} // namespace qi

#endif /* ERRORCONTROLLER_H_ */
