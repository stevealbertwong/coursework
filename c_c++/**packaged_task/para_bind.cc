/*
https://www.youtube.com/watch?v=shqvSkk8r0M&index=7&list=PL5jc9xFGsL8G3y3ywuFSvOuNm3GjBwdkb

?? when functor when just function

bind(): when functor takes more than 1 arg
http://www.cplusplus.com/reference/functional/logical_or/

predicate:
	=> functor that returns bool + does not modify data
g++ -std=c++11 para_bind.cc -o para_bind
*/
#include <iostream>
#include <functional>	// std::logical_or
#include <algorithm>    // std::transform
#include <set>
#include <vector>
#include <deque>
#include <math.h>
using namespace std;

bool needCopy(int x){
	return (x>20) || (x<3);
}

double Power(double x, double y){
	return pow(x, y);
}

void addVal(int i, int val){
	cout << i + val << endl;
}

int main(int argc, char const *argv[])
{
	set<int> myset = {2,3,4,5};
	vector<int> vec;
	deque<int> dq;

	// int x = multiplies<int>(3,4); // bulit in functor: 3 * 4

	// 1st parameter of multiplies<int>() is substituted with myset's element
	// 2nd parameter is 10
	// vec : {20, 30, 40, 50}
	// call multiply on every item of set
	transform(myset.begin(), myset.end(), // source
		back_inserter(vec), // destination
		bind(multiplies<int>(), placeholders::_1, 10)); // functor

	for(int v : vec) cout << v << endl;


	// only copy by value, does not change vec's value
	// 1st arg: placeholder, vec element
	// 2nd arg: 2
	for_each(vec.begin(), vec.end(), bind(addVal, placeholders::_1, 2));
	
	
	// use template class function to convert regular function
	// pow into functor f
	auto f = function<double (double,double)>(Power);
	transform(myset.begin(), myset.end(), 
		back_inserter(dq), 
		bind(f, placeholders::_1, 2));
	for(int d : dq) cout << d << endl;


	// predicate: functor that returns bool + does not modify data
	// very unreadable code
	deque<int> dq2;
	// when(x>20) || (x<3)
	transform(myset.begin(), myset.end(),
		back_inserter(dq2),
		bind(logical_or<bool>(), // construct functor from built in functor
			bind(greater<int>(), placeholders::_1, 20),
			bind(less<int>(), placeholders::_1, 3))
		);
	for(int d : dq2) cout << d << endl;
	
	// same as above, but more readable code
	deque<int> dq3;
	// when(x>20) || (x<3)
	transform(myset.begin(), myset.end(),
		back_inserter(dq3),
		needCopy
		);
	for(int d : dq3) cout << d << endl;

	// same as above, just demo you know lambda
	deque<int> dq4;
	// when(x>20) || (x<3)
	transform(myset.begin(), myset.end(),
		back_inserter(dq3),
		[](int x){return (x>20) || (x<3);} 
		// [](int x)-> bool{return (x>20) || (x<3);} // same as above
		);
	for(int d : dq3) cout << d << endl;
	

	return 0;
}


