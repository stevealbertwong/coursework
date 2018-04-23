#include <functional>
#include <thread>

class ThreadPool
{
public:
	ThreadPool(int numThreads);
	~ThreadPool();

	schedule(const function<void()>& thunk);

private:	
	slavesMaster();
	slaves();

	int numThreads;
	int currThreadsCount = 0;

	// struct vs class ??
	struct slave_t{
		semaphore executeSema;
		bool available; // delete it 
		function thunk;
	};
	std::vector<slave_t> slavesArmy;

	std::queue<function> functionQueue;
	std::queue<int> availableThreads;

	// why unique_ptr ??
	std::unique_ptr<semaphore> functionQueueSema;
	std::unique_ptr<semaphore> numThreadsSema; // indicates num of threads working atm

};
