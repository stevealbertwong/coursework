/**
test thread pool with my self written semaphore

using class to initialize threads with semaphore


1. optimize not spawning 10 threads right away
	=> data structure to check finished threads
	=> load_balance() + worker() spawn n monitor free n busy threads"
		
2. SafeQueue.h + SafeVector.h 
	=> atomic
	=> cleaner code with lock guard

3. why detach() 
	=> no need to write destructor to join()
	=> no need to write a vector of std::thread

functor
	=> each thread is semaphored by function_queue.empty()


*/
#include "thread-pool2.h"

using namespace std;

ThreadPool::ThreadPool(size_t numThreads) {	
	workers = vector<worker_t>(numThreads);

	max_allowed_sema.reset(new semaphore(numThreads)); 	
	tasks_sema.reset(new semaphore(0));

	num_active_threads = 0;


	for (size_t workerID = 0; workerID < numThreads; workerID++) {
		workers[workerID].ready_to_exec.reset(new semaphore(0)); 		
		workers[workerID].thunk = NULL;
	}	

	thread dt([this]() -> void { 
		this->load_balance();
	});
	dt.detach();
	

}

void ThreadPool::enqueue(const std::function<void(void)>& thunk) {
	
	tasks_lock.lock();
	tasks.push(thunk);
	tasks_lock.unlock();
		 
	// TODO: change this to notify_one()
	tasks_sema->signal();
}

void ThreadPool::load_balance() {
	while (true) {

		// wait for function attached
		tasks_sema->wait();		
		// max threads allowed(loop to get threads) 
		max_allowed_sema->wait();		

		// if no free thread, spawn new worker thread
		if(free_threads.empty()){			
			
			tasks_lock.lock(); // protect tasks, no enqueue when send to thread
			workers[num_active_threads].thunk = tasks.front();
			tasks.pop();			
			tasks_lock.unlock();

			std::thread wt([this](size_t num_active_threads) -> void {
				this->worker(num_active_threads);
			}, num_active_threads); // std:bind ??
			wt.detach();
			
			workers[num_active_threads].ready_to_exec->signal();
			num_active_threads++; 

		// if yes existing thread
		}else{
			free_threads_lock.lock();
			int id = free_threads.front();
			free_threads.pop();
			free_threads_lock.unlock();

			tasks_lock.lock();			
			workers[id].thunk = tasks.front();	
			tasks.pop();		
			tasks_lock.unlock();						
			workers[id].ready_to_exec->signal();
		}		
	}
}


/* 
1. while true loop + wait()
2. workers[id].thunk() EXECUTE!!!
3. update worker_t + available_threads->signal() 

THREAD WILL NOT DIE, IT WILL JUST WAIT TO BE REUSED AFTER ONE LOOP
MULTI-THREADED FUNCTION

worker == functor == web server logic(thunk())
its predicator == load_balance's signal, not empty(), not == 1
*/
void ThreadPool::worker(size_t id) {
	while (true) {			
		workers[id].ready_to_exec->wait();
						
		/* NOT LOCKED!!!!! OTHERWISE NOT MULTI-THREADING */		
		workers[id].thunk(); 		
		
		// usleep(5000000); // 5 secs
				
		workers[id].thunk = NULL;
		
		free_threads_lock.lock();
		free_threads.push(id);
		free_threads_lock.unlock();

		max_allowed_sema->signal();									
	}
}

// ThreadPool::~ThreadPool(){    
//     for(std::thread &worker_thread: worker_threads)
//         worker_thread.join();
// }

