#include "threadpool.h"


// the constructor just launches some amount of 
// vector<thread> workers stores lambda
ThreadPool::ThreadPool(size_t threads)
    :   stop(false)
{
    for(size_t i = 0;i<threads;++i)
        // emplace_back: appends a new object in-place at the end of queue
        workers.emplace_back(
            [this]
            {
                for(;;) // while(true)
                {
                    std::function<void()> task;

                    {
                        std::unique_lock<std::mutex> lock(this->queue_mutex);
                        // lambda inside lambda
                        this->condition.wait(lock,
                            [this]{ return this->stop || !this->tasks.empty(); });
                        
                        if(this->stop && this->tasks.empty())
                            return;
                        
                        // why move() ??
                        // move: lvalue reference + no longer available
                        task = std::move(this->tasks.front());
                        this->tasks.pop();
                    }
                    task();
                }
            }
        );
}


// add new work item to the pool
// const function<void(void)>& thunk) vs template arg
template<class F, class... Args>
auto ThreadPool::enqueue(F&& f, Args&&... args) 
    -> std::future<typename std::result_of<F(Args...)>::type>
{
    // The template parameter of std::result_of must be a signature of a function. 
    // Then, the std::result_of< >::type figures the return type of the function, 
    // which is determined by the signature. The deduced return type is stored in return_t
    using return_type = typename std::result_of<F(Args...)>::type;

    // package a function into a task to be executed in different context    
    // takes nothing as para(para is bind()) + return return_type
    // task == thread == function
    // package_task is a template class =>  what is template class ??
    // bind() is used to pass parameter into package_task => create a function object    
    // bind(functor/functionr, arg1, arg2, arg3 etc)
    auto task = std::make_shared< std::packaged_task<return_type()> >(
            std::bind(std::forward<F>(f), std::forward<Args>(args)...)
        );
    
    // get_future(): get return value of task/function
    std::future<return_type> res = task->get_future();
    {
        std::unique_lock<std::mutex> lock(queue_mutex);

        // don't allow enqueueing after stopping the pool
        if(stop)
            throw std::runtime_error("enqueue on stopped ThreadPool");

        tasks.emplace([task](){ (*task)(); });
    }
    condition.notify_one();
    return res;
}



// the destructor joins all threads
ThreadPool::~ThreadPool()
{
    {
        std::unique_lock<std::mutex> lock(queue_mutex);
        stop = true;
    }
    condition.notify_all();
    for(std::thread &worker: workers)
        worker.join();
}


