/*
https://www.youtube.com/watch?v=_ja8iizm7nk&list=PLAE85DE8440AA6B83&index=38

g++ -std=c++11 ref_arg.cc -o ref_arg
*/
#include <iostream>
using namespace std;

void passByValue(int x){
	x = 99;
}

// arg/rvalue: reference/address VS lvalue dereference 
void passByReference(int *x){
	*x = 66;	
}

int main(int argc, char const *argv[])
{
	int a = 10;
	int b = 10;
	passByValue(a);
	passByReference(&b); // pass addr/ref of b
	

	cout << a << endl; // 10
	cout << b << endl; // 66

	return 0;
}