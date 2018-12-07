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
it is just a functor and a future for return


main() thread
1. packaged_task
2. get_future()
3. lock_guard + task_.push_back(t)
4. notify_one()

thread_2
1. unique_lock + cv.wait
2. task_q.pop_front()
3. task()

g++ -std=c++11 packaged_task2.cc -o packaged_task2

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
std::mutex mu;
std::mutex print_mu;
std::condition_variable cv;

void thread1(){	

	std::packaged_task<int()> t;
	
	{
		cout << "v" << endl;
		std::unique_lock<mutex> ul(mu);
		cout << "a" << endl;
		// not [this] since not inside class
		cv.wait(ul, [](){return !task_q.empty();});
		cout << "b" << endl;
		// std::move since packaged_task is not copyable
		// i.e. cannot t = task_q.front()	
		t = std::move(task_q.front());	
		task_q.pop_front();		

	}
	// outside lock => actual meat of multi-thread
	t(); // t() is blocking, might have delayed release of unique_lock
}

int factorial(int n){
	int sum = 1;
	for (int i = n; i > 0; --i)
	{
		sum *= i;	
	}
	cout << "inside threaded function factorial()" << endl;
	return sum;
}

int main(int argc, char const *argv[])
{

	std::thread t1(thread1);
	cout << "1" << endl;
	// bind creates a function object to pass in packaged_task
	std::packaged_task<int()> t(std::bind(factorial,6));
	std::future<int> fu = t.get_future();
	{
		std::lock_guard<mutex> lg(mu);
		cout << "2" << endl;
		// move() => packaged_task not copyable
		task_q.push_back(std::move(t));
	}
	cv.notify_one(); // child thread starts to run
	cout << "3" << endl;
	
	// DEADLOCK if use mu => fu.get()
	// since lg acquires the lock => t() doesn't get called
	// => fu.get() does not get called
	// OR t() is block the release of unique_lock 
	// lockguard doesnt' get called
	{
		cout << "4" << endl;
		std::lock_guard<mutex> lg(print_mu);

		cout << "parent thread: wait for child thread return value " << fu.get() << endl;
	}
	
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
