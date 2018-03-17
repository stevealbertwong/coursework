/*
base/super/parent class

*/

#include "shape.h"

void Shape::setValues(int a, int b){
	height = a;
	width = b;	
}


void Shape::setColor(string c){	
	color = "green"; // default green if not overriden by subclass
}


void Shape::setName(){	
	name = "steven wong"; // default green if not overriden by subclass
}