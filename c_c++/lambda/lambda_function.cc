
/*
g++ -std=c++11
*/
#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
using namespace std;


// generic function pointer type => for passing function as parameters
void runFunc(std::function<void()> func){
	func();
}


int main(int argc, char const *argv[])
{
	int x = 100;


	auto lambda = [&]() -> void{
		x++;
	};

	// x is not out of scope since lambda [&] captured x	
	runFunc(lambda);
	cout << x << endl;

	return 0;
}
