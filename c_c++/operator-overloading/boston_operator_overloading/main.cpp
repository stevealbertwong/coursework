/*
newboston 
https://www.youtube.com/watch?v=q4vZIF-uMzs


https://stackoverflow.com/questions/3202136/using-g-to-compile-multiple-cpp-and-h-files
https://www.dartmouth.edu/~rc/classes/softdev_linux/complex_compile.html
// 1 line, list all the other cpp files after main.cpp
g++ -o sally main.cpp sally.cpp

// 2 lines
g++ -c main.cpp sally.cpp
g++ -o sally main.o sally.o

// 1. inherit all exception class's public n protected method and variables 
// 2. only need to include parent class header file to include class prototype 
// 3. parent constructor not inherited but will run
// 4. protected is set by parent class only for inheritance

*/


#include <iostream>
#include "sally.h" // operator + overloaded

using namespace std;

int main(int argc, char const *argv[])
{
	Sally a(23);
	Sally b(33);
	Sally c = a + b;
	
	// Sally d.num = a.add(b);

	cout << c.num << endl;


	return 0;
}

