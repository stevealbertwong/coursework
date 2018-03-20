/*
derived/sub/children class

*/

#include "child.h"

int Child::funcProtectedVariable(){
	return height * width;
}

void Child::setParentPublicVariable(string c){	
	color = c; // parent virtual function overriden
}

void Child::funcProtectedFunc(){
	protected_func();
}