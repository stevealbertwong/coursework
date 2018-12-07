/*
https://www.youtube.com/watch?v=MefRKIml_1w&index=23&list=PL5jc9xFGsL8G3y3ywuFSvOuNm3GjBwdkb

operator overloading to stream print class

e.g. mulitprocess proxy

std::ostream& operator<<(std::ostream& os, const HTTPHeader& hh) {
  for (const pair<string, string>& p: hh.headers) {
    os << p.first << ": " << p.second << "\r\n";
  }
  return os;
}

g++ -std=c++0x -o operator_overloaded_stream operator_overloaded_stream.cpp
*/

#include <sstream>
#include <string>
#include <iostream>
using namespace std;

struct Dog{
	int age;
	string name;
};

// ostream => output stream
ostream& operator<<(ostream& os, const Dog& d){
	os << d.age << " name:  " << d.name << endl;
	return os; // returning reference to the stream
}

// input stream
istream& operator>>(istream& is, const Dog& d){
	is >> d.age;
	is >> d.name;
	return is; // returning reference to the stream
}

int main(int argc, char const *argv[])
{
	Dog d{2, "Bob"}; // universal initialization from c++ 11
	cout << d;

	cin >> d;
	cout << d;

	return 0;
}