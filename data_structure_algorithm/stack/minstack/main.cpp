/*
g++ -std=c++14 -g -o0 main.cpp -o main
*/
#include "minstack.h"
#include <iostream>


int main(int argc, char const *argv[])
{
	MinStack stk;
	stk.push(10);
	stk.push(5);	
	stk.push(3);
	stk.push(2);
	stk.push(4);

	// stk.print_stack();
	// LOG(stk.head->min->data)
	stk.minimum();
	LOG(stk.global_min->data)

	stk.pop();
	stk.minimum(); // O(n)
	LOG(stk.global_min->data) // O(1)


	stk.pop();
	stk.minimum();
	LOG(stk.global_min->data)

	stk.push(1);
	stk.minimum();
	LOG(stk.global_min->data)

	stk.pop();
	stk.minimum();
	LOG(stk.global_min->data)

	return 0;
}