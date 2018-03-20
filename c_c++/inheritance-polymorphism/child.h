/*
derived/sub/children class

*/
#ifndef CHILD_H
#define CHILD_H

// superclass prototype to inherit from 
#include "parent.h"

// inheritance: all public variables n functions
// public Parent: parent's public as public + parent's protected as protected
class Child: public Parent{
	// for main
	public:
		int funcProtectedVariable();
		void setParentPublicVariable(string c);
		void funcProtectedFunc();
};

#endif