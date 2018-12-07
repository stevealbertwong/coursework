/*
newboston
https://www.youtube.com/watch?v=lX09jBr9I1s

bo qian
https://www.youtube.com/watch?v=EYuPBkgJtCQ

// other source files before main.cpp
g++ -std=c++11 -o main main.cpp parent.cpp child.cpp
./main

Access control:
1. header decide visibility to this source file
2. protected: not visible to main but visible to child class
3. private: no class or child class can access
4. class Child: public Parent => parent's public as public + parent's protected as protected
5. class Child: protected Parent => parent's public n protected become child's protected
6. class Child: private Parent => parent's public n protected become child's private

*/
#include <iostream>
#include <string>
#include "child.h"
#include "parent.h"

using namespace std;

int main()
{
	
	Child ch; 

	// main can only call header's public
	ch.setParentProtectedVariable(22, 33); // child calling parent method
	ch.setParentPublicVariable("child overriding parent's virtual setParentPublicVariable()");
	 
	cout << "child class function that access parent's protected variable " << ch.funcProtectedVariable() << endl; // 726
	ch.funcProtectedFunc();// child class function that access parent's protected function 

	cout << "in main() could only access inherited public variable" << ch.color << endl;	
	// cout << "in main CANNOT access parent's inherited protected or private variable" << ch.protected_var << endl;
	
	cout << "in main() get() bypass protected private: " << ch.getProtected() << endl;
	cout << "CAN access parent's inherited public n private variable through get()" << ch.getPrivate() << endl;
	


	// polymorphism -> parent class pointer to subclass could indirectly change its variables
	Parent *pa = &ch;
	pa->setParentProtectedVariable(10, 20);

	cout << "new area changed by parent class pointer: " << ch.funcProtectedVariable() << endl;
	// cout << "this gives error: parent does not have child's area()" << pa->area() << endl;

	pa->setName();
	cout << pa->name << endl;

	// virtual in parent overriden in children
	pa->setParentPublicVariable("blue");
	cout << pa->color << endl;
}


