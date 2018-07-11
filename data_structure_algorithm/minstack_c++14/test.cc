/*
g++ -std=c++14 test.cc -o test
*/
#include <iostream>

#define LOG(x) std::cout << x << std::endl;

class stack
{
public:
	stack(){};
	~stack(){};

	void push(const int& num){LOG("lvalue")};
	void push(int&& num){LOG("rvalue")};
	
};

int main(int argc, char const *argv[])
{
	stack s;

	int q = 10; // lvalue
	s.push(q);
	
	s.push(9); // rvalue


	for (auto v : {5, 10, 4, 9, 3, 3, 8, 2, 2, 7, 6})
    {
        s.push(v); // lvalue
        
    }
	return 0;
}