/* 
https://www.youtube.com/watch?v=EHBCF0TASa4
when the compiler see extern, it will look elsewhere for variable definition

g++ -o extern extern.cpp
*/

#include <iostream>
using namespace std;

int main(int argc, char const *argv[])
{
	extern int i;
	printf("value of i is %d\n", i);
	return 0;
}

int i = 12;