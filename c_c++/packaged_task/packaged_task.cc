/*
https://stackoverflow.com/questions/18143661/what-is-the-difference-between-packaged-task-and-async

std::packaged_task<> function wrapper to turns it asynchronous
	=> i.e. not run sequentially until task() is called
return value/exception stored internal shared state
	=> accessd through future object

1. packaged_task
2. get_future()
3. task()
4. fu.get()

g++ -std=c++11 packaged_task.cc -o packaged_task
*/

#include <iostream>
#include <future>
#include <functional>
#include <deque>
#include <thread>
#include <algorithm>
#include <utility>

//! sleeps for one second and returns 1
auto sleep_func = [](){
    std::this_thread::sleep_for(std::chrono::seconds(5));
    return 1;
};

int factorial(int n){
	int sum = 1;
	for (int i = n; i > 0; --i)
	{
		sum *= i;	
	}
	std::cout << "factorial()" << std::endl;
	return sum;
}


int main(int argc, char const *argv[])
{	

	// <int>: return int, (int) param int
	std::packaged_task<int(int)> task2(factorial);	
	task2(6); // task executed
	int sum = task2.get_future().get();
	std::cout << "sum: " << sum << std::endl;


	std::packaged_task<int()> task1(sleep_func);
	auto f = task1.get_future();
	// std::future<int> f = task.get_future(); // same
	
	task1(); // run sleep() immediately + blocking
	
	std::cout << "main() thread blocked => only available after 5 second" << std::endl;	
	std::cout << f.get() << std::endl;



	return 0;
}
