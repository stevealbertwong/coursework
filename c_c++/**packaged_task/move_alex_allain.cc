/*
https://www.cprogramming.com/c++11/rvalue-references-and-move-semantics-in-c++11.html

g++ -std=c++14 move_alex_allain.cc -o move_alex_allain
*/

#include <iostream>
using namespace std;

int x = 10;

// lvalue reference
printReference (const String& str)
{
        cout << str << "lvalue ref " << endl;
}
// rvalue reference
printReference (String&& str)
{
        cout << str << "rvalue ref " << endl;
}

// lvalue, getRef returns a reference to a global variable, so it's returning a value that is stored in a permanent location
// getRef() = 4;
int& getRef () 
{
        return x;
}
 
// rvalue, temporary object
// value being returned is not a reference to x, it's just a temporary value
int getVal ()
{
    return x;
}

// rvalue, temporary object
// getName() returns a string that is constructed inside getName()
// result of getName() is temporary object not from some value that has a fixed location
string getName()
{
    return "Alex";
}

int main(int argc, char const *argv[])
{
	/*
	Prior to C++11, temporary object use a "regular" 
	or "lvalue reference" to bind, but only if const
	const is immutable => cannot use "mutable" reference 
	as modify some object that is  about to disappear => dangerous
	
	holding on to a const reference to a temporary object ensures 
	that the temporary object isn't immediately destructed
	*/
	const string& name = getName(); // ok, lvalue reference bind
	// string& name2 = getName(); // NOT ok

	/*
	C++11, new kind of reference "rvalue reference"
	bind mutable reference to rvalue, not lvalue
	also detects temp, can be const or non-const
	*/
	const string&& name3 = getName(); // ok
	string&& name4 = getName(); // ALSO OKAY


	string me( "alex" );
	printReference(  me ); // calls the first printReference function, taking an lvalue reference
	printReference( getName() ); // calls the second printReference function, taking a mutable rvalue reference




	return 0;
}