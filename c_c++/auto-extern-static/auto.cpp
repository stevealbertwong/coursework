/*
https://www.youtube.com/watch?v=EHBCF0TASa4

g++ -o auto auto.cpp
*/

#include <iostream>
using namespace std;

void increment(){
	int i = 0;
	auto int j = 0; // like int i, by default local variable is auto
	static int h = 0; // local to source file, retains value between function call

	cout << "int i: " << i << endl;
	cout << "auto int j: " << j << endl;
	cout << "static int h: " << h << endl;
	i++;
	j++;
	h++;
}

int main(int argc, char const *argv[])
{
	increment();
	increment();
	increment();
	return 0;
}