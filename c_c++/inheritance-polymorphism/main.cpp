/*
https://www.youtube.com/watch?v=lX09jBr9I1s

// other source files before main.cpp
g++ -o main main.cpp shape.cpp square.cpp
./main
*/
#include <iostream>
#include <string>
#include "square.h"
#include "shape.h"

using namespace std;

int main()
{
	// inheritance => subclass 
	Square sq;

	// inherited shape's setvalue()
	sq.setValues(22, 33);
	 
	cout << "square's area: " << sq.area() << endl; // 726
	
	// polymorphism => parent class pointer to subclass could indirectly change its variables
	Shape *sh = &sq;
	sh->setValues(10, 20);
	
	cout << "new area changed by parent class pointer: " << sq.area() << endl;
	// cout << "this gives error: parent does not have child's area()" << sh->area() << endl;

	sh->setName();
	cout << sh->name << endl;

	// virtual in parent overriden in children
	sh->setColor("blue");
	cout << sh->color << endl;
}


