/*
cherno + mark cuban rule of 3 implementation

self implementation of string class
	=> wrapper around c char array

1. constructor => string literal to char array
2. overload copy constructor => deep copy newly created object, new ptr
	otherwise default assignment operator/copy constuctor creates shallow copy(same ptr)
3. overload assignment operator => deep copying exising object, BUT only invoked
	if object already in existence
4. [] operator overloaded to access string element
5. << operator overloaded to cout

RULE OF THREE:
if member function reference heap space i.e. ptr

g++ -std=c++14 string_class.cc -o string_class
*/
#include <iostream>

using namespace std;

class String
{
public:
	// constructor 
	String(const char* string){
		m_size = strlen(string);
		m_buffer = new char[m_size+1];
		memcpy(m_buffer, string, m_size);
		m_buffer[m_size] = 0; // null terminate
	};
	
	// overload copy constructor => deep copy => 
	// as vanilia assignment operator creates shallow copy i.e. same ptr
	String(const String& str_class){
		m_size = str_class.m_size;
		m_buffer = new char[m_size];
		memcpy(m_buffer, str_class.m_buffer, m_size);
	}

	// move constructor
	String(String&& str){
		m_buffer = nullptr;
		m_size = 0;
		m_buffer = str.m_buffer;
		m_size = str.m_size;
		str.m_buffer = nullptr;
		str.m_size = 0;
	}

	// overload assignment operator + move assignment operator
	// compiler chooses between copy n move constructor based on 
	// whether rvalue or lvalue arg
	String& operator=(const String& str){ // &: pass by ref
		
		// check self assignment by comparing addr i.e. str1 = str1
		// this == lhs's address
		if(this == &str){ // &: addr of real param(not copy)
			return *this; // deref as return real object not addr
		}

		// this: lhs of =
		// no create new as overload assignemnt => existing object	
		this->m_size = str.m_size;
		memcpy(this->m_buffer, str.m_buffer, this->m_size);
		return *this;
	}
	
	// overloading [] operator
	char& operator[](const unsigned int& index){
		return m_buffer[index];
	}

	String& operator+(const String& str){
		int size = this->m_size + str.m_size;
		char *buffer = new char[size];
		memcpy(buffer, this->m_buffer, this->m_size);
		memcpy(buffer + this->m_size, str.m_buffer, str.m_size);
		delete[] this->m_buffer;
		this->m_buffer = buffer;		
		this->m_size = size;
		return *this;
	}

	// << operator overloading
	// friend so that defintion outside class could access m_buffer
	friend std::ostream& operator<<(std::ostream & stream, const String& str);
	// friend String& operator=(const String& str);

	// crash if free twice i.e. if shallow copy same ptr
	// new[] pair w delete[]
	~String(){ delete[] m_buffer; }; 

	void debug(){
		cout << m_buffer << endl;
	}

private:
	char* m_buffer;
	unsigned int m_size;
};

// << operator overloading
// lhs: cout + rhs: String 
std::ostream& operator<<(std::ostream & stream, const String& str){
	stream << str.m_buffer;
	return stream;
}

int main(int argc, char const *argv[])
{
	String str = "steven"; // constructor invoked
	String str2 = str; // copy constructor invoked
	String str4(str2); // copy constructor invoked	
	String str5(str + str2 + str4); // copy constructor invoked
	str5.debug();
	String str6(std::move(str2)); // move constructor NOTE: segfault if move str since called later
	str6.debug();

	str[2] = 'a'; // overloaded [] operator invoked
	String str3 = "leigh";
	str3 = str; // overloaded assignment operator invoked	
	return 0;
}