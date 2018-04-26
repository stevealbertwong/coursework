/**
 * File: thread-pool.cc
 * --------------------
 * Presents the implementation of the ThreadPool class.
 
 JERRY: Incremental development is the key to arriving at a robust, bug-free executable much more quickly.

 TODO: 
 why threadpool data structure vs just threads
	=> dining philosophers: same threaded function
	=> vector<worker_t> workers: visualize threads in black box thru data structure, for debugging
	=> e.g. which request takes longest time, log no. threads available at any particular time
	=> potentially could prioritize certain requests
	=> increase or decrease threadpool depending on thread occupany rate
	=> keep track of the threads execution to reuse
	=> Launch threads flexible only when there is request coming in
 
 SafeQueue<std::function<void()>> functions_queue vs queue<function<void(void)> > functions_queue; ??
 
 what is unique_ptr ?? why ptr to semaphore ??

 dt.detach() ??
 just semaphore (new semaphore(0)) to replace lock ??
 when to lock ?? (counter, boolean flag, appending array)

future, promise ??
 threads communicate thru global var + signal atm
 future => return of thread

 Semaphores:
 ready_to_exec(worker_t)
 available_threads
 functions_queue_sem
 wait_semaphore

 why this data structure, why slave master, slave design ?? => 
 
 improvement:
 spawn all thread when initialize + when signal pass all the freeed worker ??
	=> before that worker finish work, add itself to available list
 int nofreethread + vector of available workers
 spwan a thread primarily to keep track of available worker

 */

#include "thread-pool.h"

using namespace std;


/*
CONSTRUCTOR
1. creates a vector of worker_t + initialize => (unique_ptr<semaphore> + function<void(void)>)
2. creates semaphores => unique_ptr<semaphore>.reset(new semaphore(numThreads)) 
3. launch single dispatcher thread
4. initialize each thread in threadpool

*/
ThreadPool::ThreadPool(size_t numThreads) {
	
	// create a vector of worker_threads
	workers = vector<worker_t>(numThreads);
	
	/* 
	reset(new semaphore(numThreads)) 
	=> c++ style initializing new object at heap + return pointer (unique_ptr)
	=> available_threads already declared in thread-pool.h

	*/
	// ?? does it have to be pointer ?? dining philosopher semaphore is not pointer
	available_threads.reset(new semaphore(numThreads)); // unique_ptr<semaphore>
	functions_queue_sem.reset(new semaphore(0)); // only 1 pass thru at 1 time
	wait_semaphore.reset(new semaphore(0));

	all_finished = 0;
	num_active_threads = 0;

	/* c++ style multithread class function(): create a dispatcher() thread */
	// detach() == non joinable, main() thread ends without waiting detached threads
	// this: ptr to current object threadpool e.g. this->num = num OR (*this).num = num
	// Threadpool* tp = this;
	// ?? does it have to set up pointer first before spawn dispatcher thread
	thread dt([this]() -> void { 
		this->dispatcher();
	});
	dt.detach();
	
	/* initialize each thread */
	// change order with dispatcher ??
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
// ?? review function pointer + lambda
void ThreadPool::schedule(const function<void(void)>& thunk) {
	all_finished++; // why all finished no need to lock but functions_queue need to lock ???
	f_queue_lock.lock(); // 1st time appear not in Threadpool
	functions_queue.push(thunk); // append function pointer to queue
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

/* 
Dispatcher -> pop function_queue into worker_t + dispatch/signal worker thread
THIS FUNCTION IS SINGLE THREAD

1. while true loop + double semaphore->wait()
	=> functions_queue_sem->wait();
	=> available_threads->wait();

2. double mutex locks + initialize worker threads
	=> single dispatch() compete with single schedule()
	=> single dispatch() comepte with multiple worker()
	=> thread wt([this](size_t id) -> void {this->worker(id);}, id);

3. pop function_queue to worker_t + spawn worker thread + signal worker_t semaphore
	=> workers[i].thunk = functions_queue.front();
	=> functions_queue.pop()	
	=> workers[i].ready_to_exec->signal();


NOTE: 
condition variable/semaphore is non-blocking 
=> so after class threadpool it stops at functions_queue_sem.wait()
=> once semaphore gets signaled, the following code will run
=> which means when main thread gets request 
=> pushback() + a bunch of signals, wait() + thread

because accessing worker_t struct => global copy shared resources

put blackbox threading into data structure we could log any time
*/

void ThreadPool::dispatcher() {		
	while (true) {

		/* double semaphore: wait for function (i.e. schedule) + wait for worker thread (less than numThread) 
		signal from above vs signal from below
		*/
		// ?? will there only 1 thread pass if 1st semaphore only allows 1 thread, 2nd allows many
		functions_queue_sem->wait(); // 0: SINGLE THREAD => schedule() call signal()
		available_threads->wait(); // numThreads: => block if no available threads
		
		/* single dispatch thread compete w multi worker threads */
		// ?? when lock when semaphore
		workers_lock.lock(); 
		bool found = false; // true if num_active_threads >0 && workers[i].available

		/* look for available worker thread */
		
		for (size_t i = 0; i < num_active_threads; i++) {
			if (workers[i].available) {

				workers[i].available = false; // mark it unavailable
 				
				f_queue_lock.lock(); // ?? double lock necessary => YES, COMPETE W schedule(), functions_queue is available to public through schedule()
				/* dequeue the least recently scheduled function */
				workers[i].thunk = functions_queue.front();
				functions_queue.pop();
				f_queue_lock.unlock();								
				workers[i].ready_to_exec->signal();
				
				found = true;
				break; // break for loop
			}
		}

		/* only for first time initializing spawn of worker threads
		if num_active_threads == 0 || no workers[i].available => this gets run first since num_active_threads initialize to 0 + found initialize to false */
		// ?? how to make sure spawned threads smaller than numThreads => i think need to add if(num_active_threads < numThread)
		if (!found) {
						
			workers[num_active_threads].available = false; // either 0 or last +1 (new thread)
			
			// lock => functions_queue push() pop() front() (only appears in dispatch and schedule)
			f_queue_lock.lock(); 			
			workers[num_active_threads].thunk = functions_queue.front();
			functions_queue.pop();			
			f_queue_lock.unlock();
			
			/* signal worker thread to execute it => same as above */
			// ?? this should be after creating new thread cause signal might get lost
			workers[num_active_threads].ready_to_exec->signal();			

			/* spawn new worker thread */			
			// ?? review spawning lambda thread 			
			thread wt([this](size_t num_active_threads) -> void {
				this->worker(num_active_threads);
			}, num_active_threads);
			wt.detach(); // worker thread will live forever since while(true) + no waiting/thread.join here

			num_active_threads++; /* this will not go over numThreads as this conditional is only for initializing threads*/
		}

		workers_lock.unlock();		
	}
}


/* 
1. while true loop + wait()
2. workers[id].thunk() EXECUTE!!!
3. update worker_t + available_threads->signal() 

DETACH => THREAD WILL NOT DIE, IT WILL JUST WAIT TO BE REUSED AFTER ONE LOOP
1 dispatcher thread MANY worker thread
*/
void ThreadPool::worker(size_t id) {
	while (true) {

		// ?? why reference + why lock
		// all worker threads will keep checking on signal
		workers_lock.lock(); 				
		unique_ptr<semaphore>& sem_copy = workers[id].ready_to_exec; 
		workers_lock.unlock();		
		sem_copy->wait(); // ready_to_exec signal from dispatcher()
				
		/* EXECUTE serviceRequest() + NOT LOCKED!!!!! OTHERWISE NOT MULTI-THREADING */
		workers[id].thunk(); 

		/* DISPATCHER THREAD COMPETES WTIH WORKER THREAD */
		workers_lock.lock();
		workers[id].available = true; // mark itself available so that could be selected and discovered 
		workers[id].thunk = NULL;
		workers_lock.unlock();

		available_threads->signal();
		
		// signal all requests have been dealt by worker threads
		all_finished--; // atomic so no need to lock !!!
		if (all_finished == 0) wait_semaphore->signal(); 
	}
}

