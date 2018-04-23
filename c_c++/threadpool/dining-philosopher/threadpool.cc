
// why not operator ??
ThreadPool::ThreadPool() : numThreads(int numThreads) {
	
	functionQueueSema = new Semaphore(0);
	numThreadsSema = new Semaphore(numThreads);

	thread sm([](){
		slavesMaster();
	}
	sm.detach();	


	);
}

ThreadPool::schedule(const function<void()>& thunk){
	// why not emplace_back ??
	functionQueue.push(thunk);
	functionQueueSema->signal();
}

ThreadPool::slavesMaster(){
	while(true){
		functionQueueSema->wait(); // 0-infinity
		numThreadsSema->wait(); // 0-10

		// if existing available threads
		if (availableThreads.notNull())
		{
			int slaveId = availableThreads.pop();
			slavesArmy[slaveId].available = false;
			slavesArmy[slaveId].thunk = functionQueue.pop();
			slavesArmy[slaveId].executeSema.signal();

		// only run when spawning new threads, threadpool under capacity
		} else {
			// not strictly necessary since at any given time there will only be max num threads
			// e.g. 6 spawned threads, 5 occupied threads => keep spawning till 10
			// e.g. 10 spawned, 8 occupied => only 2 will go thru semaphore and look for available
			if(numThreads < currThreadsCount) continue;
			int slaveId = currThreadsCount;
			slavesArmy[slaveId].available = false;
			slavesArmy[slaveId].thunk = functionQueue.pop();
			
			thread st([](){
				slaves(slaveId);
			});
			st.detach();

			slavesArmy[slaveId].executeSema.signal();
			
			currThreadsCount++;
		}

		}
	}
}

ThreadPool::slaves(int slaveId){
	while(true){
		slavesArmy[slaveId].executeSema->wait();
		thunk = slavesArmy[slaveId].pop();
		thunk();
		slavesArmy[slaveId].available = true;
		availableThreads.push(slaveId);
		
		
		numThreadsSema->signal;

	}

}
