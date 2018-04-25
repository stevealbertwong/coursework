/**

 */

#ifndef _thread_pool_
#define _thread_pool_

#include <cstddef>     // for size_t
#include <functional>  // for the function template used in the schedule signature
#include <queue>
#include <thread>
#include <vector>
#include "semaphore.h" 
#include <algorithm>
#include <iomanip>
#include <atomic>
#include <iostream>
using namespace std;


class ThreadPool {
 public:
 	ThreadPool(size_t numThreads);
 	void schedule(const std::function<void(void)>& thunk);
 	void wait();
 	
 private:
 	struct worker_t{		
		unique_ptr<semaphore> ready_to_exec;
		function<void(void)> thunk;
	}typedef worker_t;

	mutex num_active_threads_lock;
	mutex workers_lock;
	mutex f_queue_lock;
	mutex free_threads_lock;

	atomic_int all_finished;
	size_t num_active_threads;

 	unique_ptr<semaphore> available_threads;
 	unique_ptr<semaphore> functions_queue_sem;
 	unique_ptr<semaphore> wait_semaphore;
 	
 	// queue_ts + vector_ts => atomic/thread safe
 	vector<worker_t> workers;
 	queue<function<void(void)> > functions_queue;
 	queue<int> free_threads;
 	
 	void dispatcher();
 	void worker(size_t id);

  ThreadPool(const ThreadPool& original) = delete;
  ThreadPool& operator=(const ThreadPool& rhs) = delete;
};

#endif
