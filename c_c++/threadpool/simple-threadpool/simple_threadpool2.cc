/*
https://codereview.stackexchange.com/questions/126026/threadpool-implementation-in-c11
*/
#include <vector>
#include <queue>
#include <memory>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <future>
#include <functional>
#include <iostream>
#include <stdexcept>
#include <unistd.h>

// Class: ThreadPool
class ThreadPool {

  // Class: Worker
  class Worker {

    public:

    // Constructor.
    explicit Worker(ThreadPool* master) : _master{master} {};

    // Functor.
    void operator ()() {

      ::std::function<void()> task;

      while(true) {
        { // Acquire lock.
          ::std::unique_lock<::std::mutex> lock(_master->_mutex);

          _master->_condition.wait(
            lock,
            [&] () { return !_master->_tasks.empty() || _master->_terminate.load(); }
          );      

          if(_master->_terminate.load()) return;

          task = _master->_tasks.front();
          _master->_tasks.pop_front();
        } // Release lock.

        task();
      }
    }

    private:

    ThreadPool* _master;
  };

  public:

    ThreadPool(size_t);
    template<class F>
    void enqueue(F f);
    ~ThreadPool();

    ThreadPool(const ThreadPool&) = delete;
    ThreadPool& operator = (const ThreadPool&) = delete;

  private:

    friend class Worker;

    ::std::vector< ::std::thread > _workers;
    ::std::deque< ::std::function<void()> > _tasks;
    ::std::mutex _mutex;
    ::std::condition_variable _condition;
    ::std::atomic_bool _terminate {false};
};

// Constructor
ThreadPool::ThreadPool(size_t threads) {
  for(size_t i = 0;i<threads;++i) {
    _workers.push_back(::std::thread(Worker(this)));
  }
}

// Destructor.
ThreadPool::~ThreadPool() {
  _terminate.store(true);
  _condition.notify_all();
  for(auto& t : _workers) t.join();
}

// Procedure: enqueue
template<class F>
void ThreadPool::enqueue(F f) {

  { // Acquire lock
    ::std::unique_lock<::std::mutex> guard(_mutex);
    _tasks.push_back(::std::function<void()>(f));
  } // Release lock

  // wake up one thread
  _condition.notify_one();
}

void foo() {
  printf("hello by %p\n", ::std::this_thread::get_id());
  sleep(1); 
}

int main() {


  ThreadPool tp(4);

  while(1) {

    printf("main %p: enque\n", ::std::this_thread::get_id());
    tp.enqueue(foo);
    sleep(1);
  }

  return 0;
}