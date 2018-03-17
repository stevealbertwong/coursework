/* 
https://www.youtube.com/watch?v=EHBCF0TASa4

global variable is okay, but problematic if duplicated local variable

global variable needs global resolution to be referenced 
when duplicate local variable

g++ -o global global.cpp
*/

#include <iostream>
using namespace std;

int i = 12; // global variable
int main(int argc, char const *argv[])
{
	int i; // if commented out, global variable referenced first
	printf("value of i is %d\n", i); // 0 
	printf("value of i after global resolution is %d\n", ::i); // 12
	return 0;
}

