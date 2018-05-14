/*
https://www.youtube.com/watch?v=EHBCF0TASa4

http://www.learncpp.com/cpp-tutorial/43-static-duration-variables/

One of the most common uses for static duration local variables 
is for unique identifier generators. 

g++ -o static static.cpp
*/

#include <iostream>
using namespace std;

void increment(){
	int i = 0;
	auto int j = 0; // like int i, by default local variable is auto
	static int h = 0; // local to source file, retains value between function call

	cout << "int i: " << i << endl;
	cout << "auto int j: " << j << endl;
	// only static keeps incrementing
	cout << "static int h: " << h << endl;
	i++;
	j++;
	h++;
}

int generateID()
{
    static int s_itemID = 0;
    // s_itemID is a local variable, it can not be “tampered with” by other functions
    // makes copy of s_itemID, increments the real s_itemID, then returns the value in the copy
    return s_itemID++; 
}

int main(int argc, char const *argv[])
{
	increment();
	increment();
	increment();
	// cout << h << endl; // error
	return 0;
}