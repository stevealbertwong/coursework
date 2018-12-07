/*
https://www.youtube.com/watch?v=SZQ6-pf-5Us&t=10s
future: parent wait for return from child thread
promise: child wait for return from parent

async()
	creates new sychronizing thread 
	cut the needs of cv.wait()/cv.signal() to synchronize between threads

package_task()

g++ -std=c++11 future.cc -o future
*/
#include <iostream>
#include <future>
using namespace std;

int factorial(int n){
	int sum = 1;
	for (int i = n; i > 0; --i)
	{
		sum *= i;	
	}
	return sum;
}

int main(int argc, char const *argv[])
{
	
	// default is std::launch::deferred|std::launch::async
	// i.e. depends on implementation
	// future<int> fu = async(factorial, 4);


	// std::launch::async => new child thread create right away
	// future datatype is a channel to get return from child thread
	future<int> fu = async(std::launch::async, factorial, 4); 


	// std::launch::deferred: defer spawning/parent thread until get() is called
	// execute in the same thread
	// future<int> fu = async(std::launch::deferred, factorial, 4);
	 

	// wait until child thread finish to get return value from child thread
	// like parent calling cv.wait() and child calling cv.signal()
	// future could call get() once, if called again crash
	// return value from child thread
	int sum = fu.get();
	cout << sum << endl;

	return 0;
}

