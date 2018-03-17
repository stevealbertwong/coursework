/*
derived/sub/children class

*/

#include "square.h"

int Square::area(){
	return height * width;
}

void Square::setColor(string c){	
	color = c; // parent virtual function overriden
}