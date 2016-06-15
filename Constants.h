/*
 * Constants.h
 *
 *  Created on: Apr 20, 2016
 *      Author: guille
 */

#ifndef CONSTANTS_H_
#define CONSTANTS_H_

namespace constants {

/********** Configurable parameters *************/

const short VECTORMAXSIZE = 40;
const short NUMBEROFBITS = 5;

/***********************************************/

const short NOVALUE = 0;

// Type of gates
const short TYPEX = 1;
const short TYPEY = 2;
const short TYPEZ = 3;
const short TYPEID = 4;
const short TYPEH = 5;
const short TYPES = 6;
const short TYPET = 7;
const short TYPETDG = 8;
const short TYPESDG = 9;
const short TYPEMEASURE = 10;
const short TYPEBLOCH = 11;

const short TYPESCXFROM = 12;
const short TYPESCXTO = 13;

const short NOTFOUND = 14;

const short OK = 15;

// Errors
const short ERROR = 16;
const short ERROROUTOFBOUNDS = 16;
const short ERRORNOMEASURES = 17;
const short ERRORBLOCHANDMEASURE = 18;
const short ERRORNOGATESAFTERMEASURES = 19;

// Bit states
const short BITSTATENOINITIALIZED = 20;
const short BITSTATECLOSED = 21; // After a measure
const short BITSTATEOPEN = 22;
}

#endif /* CONSTANTS_H_ */
