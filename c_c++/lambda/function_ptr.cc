/*
function pointer: ptr represents addr of function/cpu instructions in RAM
assign function to variable

https://www.youtube.com/watch?v=ynYtgGUNelE
https://www.youtube.com/watch?v=p4sDgQ-jao4

g++ -std=c++11 function_ptr.cc -o function_ptr
*/
#include <iostream>
using namespace std;

#define LOG(x) cout << x << endl;

int Add(int a, int b){return a+b;}
int main(){	
	
	// int (*func)(int, int); // declare function ptr
	// auto func = Add; // auto==int(*func)() , the actual type

	// very confusing syntax => using or typedef => to create alias
	
	typedef int (*func)(int, int); // func is alias name
	func add_func = Add;

	// &Add but implicit conversion, memory addr of function
	// same as above => auto == typedef int (*func)(int, int)
	// auto add_func = Add; 

	int c = add_func(2,3);
	LOG(c);

}