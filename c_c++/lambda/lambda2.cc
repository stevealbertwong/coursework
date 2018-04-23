/*
c++ lambda function
https://www.youtube.com/watch?v=uk0Ytomv0wY&t=260s

g++ -std=c++11 lambda2.cc -o lambda2
*/
#include <functional>
#include <iostream>
using namespace std;


int main(int argc, char const *argv[])
{
	int i = 10;
	int g = 11;
	
	// i, g is local to main but outside of scope of lambda
	// cannot change i as pass by value
	// can change g as pass by reference
	// [=] => pass in every local variables by value inside main()
	// [&] => same but by reference
	// [&, i] => capture i by value, everything else by reference
	// lambda with no return type is auto
	auto sayHi = [i, &g](int a, int b) -> int{
		g = 100;
		return a + b + i + g;
	};

	
	// int (*sayHi)(int, int)
	
	// std::function<int(int, int)> sayHi = [i, &g](int a, int b) -> int{
	// 	g = 100;
	// 	return a + b + i + g;
	// };

	cout << sayHi(10, 20) << endl;
	return 0;
}