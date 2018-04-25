/**
test thread pool with my self written semaphore

using class to initialize threads with semaphore


1. optimize not spawning 10 threads right away
	=> data structure to check finished threads
	=> dispatcher() + worker() spawn n monitor free n busy threads"
		
2. SafeQueue.h + SafeVector.h 
	=> atomic
	=> cleaner code with lock guard

3. why detach()

functor
	=> each thread is semaphored by function_queue.empty()


*/
#include <functional>
#include "thread-pool.h"

using namespace std;

ThreadPool::ThreadPool(size_t numThreads) {	
	workers = vector<worker_t>(numThreads);

	available_threads.reset(new semaphore(numThreads)); 
	functions_queue_sem.reset(new semaphore(0)); 
	wait_semaphore.reset(new semaphore(0));

	all_finished = 0;
	num_active_threads = 0;
	
	thread dt([this]() -> void { 
		this->dispatcher();
	});
	dt.detach();
	
	
	for (size_t workerID = 0; workerID < numThreads; workerID++) {
		workers[workerID].ready_to_exec.reset(new semaphore(0)); 
		workers[workerID].available = false;
		workers[workerID].thunk = NULL;
	}
}

/* schedule -> queue up thunk semaphore way + signal functions_queue_semaphore */
// append the provided function pointer to the end of the queue of function pointers
// const function<void(void)>& thunk -> C++11 way to type a function pointer 
// that can be invoked without any arguments

// workers.schedule([this,p]{handler.ServiceRequest(p)})
/*
https://stackoverflow.com/questions/20353210/usage-and-syntax-of-stdfunction
function<void(void)> => <void> == return void, () == take void as argument

*/
void ThreadPool::enqueue(const std::function<void(void)>& thunk) {
	all_finished++; 
	f_queue_lock.lock(); // 1st time appear not in Threadpool
	functions_queue.push(thunk); // append function point to queue
	f_queue_lock.unlock();
	
	 
	// once dispatcher notified schedule return right away => you sure ??s
	// so more functions can be scheduled
	functions_queue_sem->signal();
}


// wait until all requests threaded serviceRequest() finishes => return
void ThreadPool::wait() {
	wait_semaphore->wait();
	return;
}


void ThreadPool::dispatcher() {		
	
	while (!function_queue.empty()) {		

		// => delete since whether thread shd run depends on function_queue
		// max threads allowed(loop to get threads)
		// functions_queue_sem->wait(); 
		
		// 
		available_threads->wait(); 
		

		workers_lock.lock(); 
		bool found = false; // true if num_active_threads >0 && workers[i].available

		if (num_active_threads == numThreads) continue;

		// if no existing thread, spawn new slave thread
		if(free_threads.empty()){
			
			f_queue_lock.lock(); 			
			workers[num_active_threads].thunk = functions_queue.front();
			functions_queue.pop();
			f_queue_lock.unlock();
			
			/* signal worker thread to execute it => same as above */
			// this should be after creating new thread ??
			workers[num_active_threads].ready_to_exec->signal();			

			/* spawn new slave thread */			
			thread wt([this](size_t num_active_threads) -> void {
				this->worker(num_active_threads);
			}, num_active_threads);
			wt.detach(); // worker thread will live forever since while(true) + no waiting/thread.join here
			cout << "F" << endl;
			
			// num_active_threads_lock.lock();
			num_active_threads++; 

		// if yes existing thread
		}else{
			free_threads_lock.lock()
			int id = free_threads.pop();
			free_threads_lock.unlock()

			f_queue_lock.lock(); // ?? double lock necessary => YES, COMPETE W schedule(), functions_queue is available to public through schedule()
			/* dequeue the least recently scheduled function */
			workers[id].thunk = functions_queue.front();
			functions_queue.pop();
			f_queue_lock.unlock();
			
			/* signal worker thread to execute it => same as below */
			workers[id].ready_to_exec->signal();

		}

		workers_lock.unlock();
		
	}
}


/* 
1. while true loop + wait()
2. workers[id].thunk() EXECUTE!!!
3. update worker_t + available_threads->signal() 

THREAD WILL NOT DIE, IT WILL JUST WAIT TO BE REUSED AFTER ONE LOOP
MULTI-THREADED FUNCTION

worker == functor
its predicator == dispatcher's signal, not empty(), not == 1
*/
void ThreadPool::worker(size_t id) {
	while (true) {

		// ?? why copy + why lock	
		workers_lock.lock(); 				
		unique_ptr<semaphore>& sem_copy = workers[id].ready_to_exec; 
		workers_lock.unlock();		
		sem_copy->wait(); // ready_to_exec signal from dispatcher()
				
		/* EXECUTE serviceRequest() + NOT LOCKED!!!!! OTHERWISE NOT MULTI-THREADING */
		
		workers[id].thunk(); 
		cout << id << endl;

		/* DISPATCHER THREAD COMPETES WTIH WORKER THREAD */

		usleep(5000000); // 10 secs
		workers_lock.lock();
		workers[id].available = true; // mark itself available so that could be selected and discovered 
		workers[id].thunk = NULL;
		workers_lock.unlock();		

		free_threads.lock();
		free_threads.push_back(id);
		free_threads.unlock();

		available_threads->signal();
		
		
		// signal all requests have been dealt by worker threads
		all_finished--;
		if (all_finished == 0) wait_semaphore->signal(); 
	}
}

