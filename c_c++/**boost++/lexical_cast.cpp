/*
https://www.youtube.com/watch?v=r-ziiln0Hj8&t=1s

g++ -std=c++11 -o lexical_cast lexical_cast.cpp
*/
#include <iostream>
#include <string>
#include <boost/lexical_cast.hpp> // safe, efficient, convenient other data type from and to string
using boost::lexical_cast;
using namespace std;

int main(int argc, char const *argv[])
{
	int s = 23;
	string str = lexical_cast<string>(s);
	cout << str << endl;
	str = "Message: " + lexical_cast<string>('A') + "=" + lexical_cast<string>(34.5);
	cout << str << endl;


	return 0;
}