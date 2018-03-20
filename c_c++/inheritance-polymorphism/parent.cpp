/*
base/super/parent class

*/

#include "parent.h"

void Parent::setParentProtectedVariable(int a, int b){
	height = a;
	width = b;	
}

void Parent::setParentPublicVariable(string c){	
	color = "green"; // default green if not overriden by subclass
}

void Parent::setName(){	
	name = "steven wong"; // default green if not overriden by subclass
}