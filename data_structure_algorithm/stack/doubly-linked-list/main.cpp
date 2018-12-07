/*
g++ -std=c++14 -g -o0 main.cpp -o main
*/
// #include "Stack.h"
#include "stack.h"
#include <iostream>


int main(int argc, char const *argv[])
{
	Stack stk;
	stk.push_front(10);
	stk.push_front(5);
	stk.push_back(1);
	stk.push_back(3);
	stk.push_back(90);
	stk.push_front(46);
	stk.pop_front();
	stk.pop_back();
	stk.print_stack();
	// stk.pop();
	// stk.print_stack();
	// stk.max();
	// LOG(stk.getMinimum())

	return 0;
}