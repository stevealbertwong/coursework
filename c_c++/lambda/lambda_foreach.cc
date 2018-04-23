/*
c++ lambda function
https://www.youtube.com/watch?v=uk0Ytomv0wY&t=260s

g++ -std=c++11 lambda3.cc -o lambda3

*/
#include <iostream>
#include <vector>
#include <algorithm> // for_each
using namespace std;


int main(int argc, char const *argv[])
{
	vector<int> arr = {1,2,3,4,5};
	double total = 0;

	// for_each 3 args: 1st, 2nd iterators, 3rd func
	// & is to pass in total
	// x is for iterators as parameters
	std::for_each(begin(arr), end(arr), [&](int x){total += x;});
	// std::for_each(arr.begin(), arr.end(), [&](int x){total += x;}); // same
	cout << total << endl;

	return 0;
}