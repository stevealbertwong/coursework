/**
 * File: thread-pool.h
 * -------------------
 * This class defines the ThreadPool class, which accepts a collection
 * of thunks (which are zero-argument functions that don't return a value)
 * and schedules them in a FIFO manner to be executed by a constant number
 * of child threads that exist solely to invoke previously scheduled thunks.
 
check out another thread pool
https://github.com/rvaser/thread_pool/tree/25d086454240d2d9e1b5a85a03be6faf61347f91

 */

#ifndef _thread_pool_
#define _thread_pool_

#include <cstddef>     // for size_t
#include <functional>  // for the function template used in the schedule signature
#include <queue>
#include <thread>
#include <vector>
#include "semaphore.h" // this file is on stanford machine, write it yourself
// #include "ostreamlock.h" // same
#include <algorithm>
#include <iostream>
#include <iomanip>
#include <atomic> // atomic_int
using namespace std;


class ThreadPool {
 public:

/**
 * Constructs a ThreadPool configured to spawn up to the specified
 * number of threads.
 */
 	ThreadPool(size_t numThreads);

/**
 * Schedules the provided thunk (which is something that can
 * be invoked as a zero-argument function without a return value)
 * to be executed by one of the ThreadPool's threads as soon as
 * all previously scheduled thunks have been handled.
 */
// the func to be scheduled is expected to return void
// => no need for future or promise
 	void schedule(const std::function<void(void)>& thunk);

/**
 * Blocks and waits until all previously scheduled thunks
 * have been executed in full.
 */
 	void wait();
  
/*
DATA STRUCTURE:
1. vector<worker_t> workers 
	=> store all threads' thunk, availability, ready_to_exe semaphore
	=> programmer's interface to watch how many threads are left/available
2. semaphores 
	available_threads, functions_queue_sem, wait_semaphore
3. mutex
4. queue<function<void(void)>> function_queue
	function that returns void n takes void parameters
*/
 private:
 	struct worker_t{
		bool available;
		unique_ptr<semaphore> ready_to_exec;
		function<void(void)> thunk;
	}typedef worker_t;

	mutex workers_lock;
	mutex f_queue_lock;

	// https://baptiste-wicht.com/posts/2012/07/c11-concurrency-tutorial-part-4-atomic-type.html
	// std::atomic: lock free operation and so thread safe, performance better than lock
	// ?? why not make many data type atomic
	atomic_int all_finished; 
	size_t num_active_threads;

	// unique_ptr: smart ptr, when new, no need delete
 	unique_ptr<semaphore> available_threads;
 	unique_ptr<semaphore> functions_queue_sem;
 	unique_ptr<semaphore> wait_semaphore;
 	
 	vector<worker_t> workers;
	 /* c++ style queue of functions 
	 https://stackoverflow.com/questions/22579697/what-is-a-stack-queue-vector-array-and-list
	 */
 	queue<function<void(void)> > functions_queue;
 	
 	void dispatcher();
 	void worker(size_t id);
 	

/**
 * ThreadPools are the type of thing that shouldn't be cloneable, since it's
 * not clear what it means to clone a ThreadPool (should copies of all outstanding
 * functions to be executed be copied?).
 *
 * In order to prevent cloning, we remove the copy constructor and the
 * assignment operator.  By doing so, the compiler will ensure we never clone
 * a ThreadPool.
 */
  // https://www.ibm.com/developerworks/community/blogs/5894415f-be62-4bc0-81c5-3956e82276f3/entry/deleted_functions_in_c_11?lang=en
  // forbid copy or assignment operations between class objects.
  // i.e. CANNOT ThreadPool tp2 = tp1; or tp3 = tp1;
  // object copy constructor disabled
  ThreadPool(const ThreadPool& original) = delete;
  // object assignment operator disabled
  ThreadPool& operator=(const ThreadPool& rhs) = delete;
};

#endif
