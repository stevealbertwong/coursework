/*
https://www.youtube.com/watch?v=SZQ6-pf-5Us&t=10s
future: parent wait for return from child thread
promise: child wait for return from parent

child wait for parent's argument
	p.set_value(4);

parent then wait for child's return value
	int sum = fu.get();

*/

#include <iostream>
#include <future>
using namespace std;

// pass future as parameter reference
// child wait for parent's future package to fulfill promise
int factorial(future<int>& f){
	
	// get() throw exception if parent does not pass future
	// std::future_errc::broken_promise
	int n = f.get();
	int sum = 1;
	for (int i = n; i > 0; --i)
	{
		sum *= i;	
	}
	return sum;
}


int main(int argc, char const *argv[])
{	
	// parent promise child to send a value in future
	// future here is like a package that parent send to child
	// child thread 
	promise<int> p;
	// value parent passing to child is int
	future<int> f = p.get_future();


	// cannot p2 = p1: has to use move
	std::promise<int> p2 = std::move(p);


	// std::ref() pass parameter by reference
	// value passed back by parent is int
	future<int> fu = async(std::launch::async, factorial, ref(f)); // making sure new thread will be born

	// parent fulfilling promise to set value 4
	// child thread starts to run when getting value 4	
	p.set_value(4);
	
	
	// parent waiting for child to finish
	int sum = fu.get();
	cout << sum << endl;

	return 0;
}

/*

auto f = std::async(std::launch::async, 
    [](int a, int b) { return a + b; }, 2, 3);
std::cout << f.get() << '\n';

*/

