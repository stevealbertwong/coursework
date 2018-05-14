/*
g++ -std=c++11 ptr_ref.cc -o ptr_ref

https://www.youtube.com/watch?v=Fa6S8Pz924k&index=37&list=PLAE85DE8440AA6B83
*/
#include <iostream>
using namespace std;

int main(int argc, char const *argv[])
{
	int i =5; // uninitialized variable close to stack
	int r = i; // uninit var close to stack 
	int &t = i; // reference=> alias of i that does not exist in memory
	// int *p = i; // error
	int &a = t; // alias of alias
	int *p = &i; // point at address of i var
	int *g = &t;

	cout << i << endl; // 5
	cout << &i << endl; // addr
	cout << r << endl;
	cout << &r << endl; // different addr
	cout << t << endl; // 5
	cout << &t << endl; // same addr
	cout << a << endl; // 5
	cout << &a << endl; // same addr
	// cout << *t << endl; // error
	cout << *p << endl;
	cout << p << endl;
	cout << *g << endl;
	cout << g << endl;

	

	return 0;
}