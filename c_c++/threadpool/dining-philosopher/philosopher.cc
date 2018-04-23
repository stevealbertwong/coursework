#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include <cstdlib> 
#include <chrono>
#include <unistd.h>

#include "threadpool.h" // threadpool.schedule()
using namespace std;

// ?? static
const unsigned int kNumPhilosophers = 3;
const unsigned int kNumForks = kNumPhilosophers;
const unsigned int kNumMeals = 10;

const mutex forks[kNumForks];
const mutex streamLock;

// simulate threads starting at different time
void randomizeStartTime(int num){
	std::this_thread::sleep_for(std::chrono::milliseconds(rand()%2000+100));
	// sleep(rand()%3);
		
	streamLock.lock();
	cout << " i am thinking : from thread" << num << endl;
	streamLock.unlock();
}

void eat(int id){
	int left = id;
	int right = (id+1) % kNumPhilosophers;
	forks[left].lock();
	std::this_thread::sleep_for(std::chrono::milliseconds(rand()%1000+900));
	forks[right].lock();

	forks[left].lock();
	forks[right].lock();
}

void philosopher(int id){
	for (int i = 0; i < kNumMeals; ++i)
	{
		randomizeStartTime(id);
		eat(id);
	}
}



int main(int argc, char const *argv[])
{
	ThreadPool threadpool(2);
	for (int i = 0; i < kNumPhilosophers; ++i)
	{	
		// or [this] or [] or [this, i] ??
		threadpool.schedule([&](int i){philosopher(i)})
	}


	
	return 0;
}