/*

http://thispointer.com/c11-multithreading-part-10-packaged_task-example-and-tutorial/
https://www.youtube.com/watch?v=FfbZfBk-3rI&t=15s


why package task?? packaged_task() vs async()
	=> packaged_task: data type tht stores funct, runs it, notify when done
	=> bind seems also gets the job done

	auto t = std::bind(factorial,6);
	t();
	
	=> link callable object to a future

std::packaged_task by itself has nothing to do with threads: 
it is just a functor and a related future
*/

#include <iostream>
#include <future>
#include <functional>
#include <deque>
#include <thread>
#include <algorithm>
#include <utility>
using namespace std;

std::deque<packaged_task<int()>> task_q;

void thread1(){	
	// std::move since not copyable, cannot t = task_q.front()
	packaged_task<int()> t = move(task_q.front());
	// invoke function wrapped in packaged task 
	t();
}

int factorial(int n){
	int sum = 1;
	for (int i = n; i > 0; --i)
	{
		sum *= i;	
	}
	cout << sum << endl;
	return sum;
}

int main(int argc, char const *argv[])
{
	// pass to function/object/thread
	// std::packaged_task<int(int)> pt(factorial);	
	// pt(6); // task executed
	// int sum = pt.get_future().get();
	// cout << sum << endl;

	// bind creates a function object to pass in packaged_task
	// std::packaged_task<int()> pt(std::bind(factorial,6));
	// pt();


	thread t1(thread1);
	std::packaged_task<int()> t(std::bind(factorial,6));
	std::future<int> fu = t.get_future();

	task_q.push_back(pt);
	cout << fu.get() << endl;
	t1.join();

	return 0;
}

/*
https://stackoverflow.com/questions/18143661/what-is-the-difference-between-packaged-task-and-async

auto f = std::async(std::launch::async, 
    [](int a, int b) { return a + b; }, 2, 3);
std::cout << f.get() << '\n';


std::packaged_task<int(int,int)> task([](int a, int b) { return a + b; });
auto f = task.get_future();
task(2,3);
std::cout << f.get() << '\n';


*/
