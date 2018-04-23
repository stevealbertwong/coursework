/*
g++ -std=c++11 test.cc -o test
*/
#include <iostream>
using namespace std;

int main(int argc, char const *argv[])
{
	int i =5; // uninitialized variable close to stack
	int r = i; // uninit var close to stack 
	int &t = i; // reference, pure copy of i that does not exist in memory
	// int *p = i; // error

	cout << i << endl;
	cout << &i << endl;
	cout << r << endl;
	cout << &r << endl;
	cout << t << endl;
	cout << &t << endl;
	// cout << *t << endl; // error

	return 0;
}