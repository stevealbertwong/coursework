/*

what is stream ?
	=> controls external device(file system, network, monitor, stdin)
	=> serial io interface to external device, handle io data one by one
	
2 steps for every io
	1. format data in normal ways
	2. io using api of external devices

iostream: input output stream
cout: global object of ostream that lives in std namespace
ostream: typedef basic_ostream<char> ostream

<<: ostream& ostream::operator<< (string v) 
	=> member function of ostream
	=> returning reference therefore could chain tgt
endl: '\n' + flush()

bo qian 
stream
https://www.youtube.com/watch?v=hk5NYscSPHI&list=PL5jc9xFGsL8G3y3ywuFSvOuNm3GjBwdkb&index=17

stringstream
https://www.youtube.com/watch?v=VzM1GWUl8eI&list=PL5jc9xFGsL8G3y3ywuFSvOuNm3GjBwdkb&index=22

g++ -o stream stream.cpp
*/
#include <fstream> // ifstream, getline()
#include <iostream> 
#include <sstream>// ostringstream
using namespace std;

int main(int argc, char const *argv[])
{
	
	// of destructred when goes out of scope (RAII) resource acquisition is initialization
	ofstream of("mylog.txt"); // create new file if not exist
	// could write all datatypes when ioing external device
	of << "hi i am cool" << endl;
	of << 123 << endl;
	of << 123.3333333 << endl;
	of << bitset<8>(14) << endl; // stl datatypes, 00001110
	// of << complex<int>(2,3) << endl;
	

	// endl => function


	// formatted io



	// member functions that handles unformatted io




	// stringstream => stream class that piece format n extract string 
	// but does not have io operations	
	
	ostringstream oss; // only format output, better type safety + readable
	istringstream iss; // only format input
	stringstream ss; // both format output n input

	ss << 89 << "  hex:  " << hex << 89 << "   oct:   " << oct << 89;
	// 89  hex:  59   oct: 131
	string pieced_tgt_string = ss.str(); // must turn stream back to string
	cout << pieced_tgt_string << endl;

	// formatted input token by token, separated by space, tab, '\n' newline
	int a, b, c; 
	string s1, s2;
	
	ss >> hex >> a; // pass 89 as hex == dec 137	
	cout << a << endl;

	ss >> s1; // 2nd token is string, s1: "hex:"
	cout << s1 << endl;

	ss >> dec >> b; // b == 59
	cout << b << endl;

	// ss.ignore(6); // ignore next 6 characters i.e. oct:
	ss >> s2;

	ss >> oct >> c; // 131 as oct => dec 89
	cout << c << endl;





	return 0;
}