/*
derived/sub/children class

*/
#ifndef SQUARE_H
#define SQUARE_H

// superclass prototype to inherit from 
#include "shape.h"

// inheritance: all public variables n functions
class Square: public Shape{
	public:
		int area();
};

#endif