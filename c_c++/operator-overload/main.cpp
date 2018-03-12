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

