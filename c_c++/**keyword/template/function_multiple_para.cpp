/*
newboston 
https://www.youtube.com/watch?v=SeleR7PDs5Q

if more than 1 type of data in function parameters,
need to define 2 generic data type in template

g++ function_multiple_para.cpp -o function_multiple_para

*/

#include <iostream>
using namespace std;

// class n typename in basic cases are interchangeable
template <class FIRST, class SECOND>
FIRST smaller(FIRST a, SECOND b){
	return (a<b?a:b); // if a smaller than b returns a, else returns b
}

int main(int argc, char const *argv[])
{
	int x = 89;
	double y = 56.78;
	cout << smaller(x,y) << endl; // 56 since return int(SECOND)
	cout << smaller(y,x) << endl; // 56.78 since return double(FIRST)
		
	return 0;
}