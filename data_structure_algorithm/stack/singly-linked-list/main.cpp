/*
g++ -std=c++14 -g -o0 main.cpp -o main
*/
// #include "Stack.h"
#include "stack.h"
#include <iostream>


int main(int argc, char const *argv[])
{
	Stack stk;
	stk.push(10);
	stk.push(7);
	stk.push(5);
	stk.push(3);
	stk.push(1);
	stk.print_stack();
	

	stk.reverse();
	
	// stk.pop();
	// stk.print_stack();
	// stk.max();
	// LOG(stk.getMinimum())

	return 0;
}
