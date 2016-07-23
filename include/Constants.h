/*
 * Constants.h
 *
 *  Created on: Apr 20, 2016
 *      Author: guille
 */

#ifndef CONSTANTS_H_
#define CONSTANTS_H_

namespace qi 
{

#define NOVALUE 0

// Type of gates
#define TYPEX 1
#define TYPEY 2
#define TYPEZ 3
#define TYPEID 4
#define TYPEH 5
#define TYPES 6
#define TYPET 7
#define TYPETDG 8
#define TYPESDG 9
#define TYPEMEASURE 10
#define TYPEBLOCH 11

#define TYPESCXFROM 12
#define TYPESCXTO 13

#define NOTFOUND 14

#define OK 15

// Errors
#define ERROR 16
#define ERROROUTOFBOUNDS 17
#define ERRORNOMEASURES 18
#define ERRORBLOCHANDMEASURE 19
#define ERRORNOGATESAFTERMEASURES 20

// Bit states
#define BITSTATENOINITIALIZED 21
#define BITSTATECLOSED 22 // After a measure
#define BITSTATEOPEN 23

/********** Configurable parameters *************/

const short VECTORMAXSIZE = 40;
const short NUMBEROFBITS = 5;

/***********************************************/

} // namespace qi

#endif /* CONSTANTS_H_ */
