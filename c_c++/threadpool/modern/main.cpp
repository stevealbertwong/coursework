/*
g++ -std=c++11 

*/
#include <iostream>
#include <vector>
#include <chrono>

#include "threadpool.h"

int main()
{        
    ThreadPool pool(4);
    // future: return value of package task/promise/threads
    std::vector< std::future<int> > results;

    for(int i = 0; i < 8; ++i) {
        results.emplace_back(
            // ?? why lambda no (), when pass thru [] when pass thru ()            
            pool.enqueue([i] {                
                std::cout << "hello " << i << std::endl;                
                std::this_thread::sleep_for(std::chrono::seconds(1));                
                std::cout << "world " << i << std::endl;                
                return i*i;
            })
        );
    }

    for(auto && result: results)
        std::cout << result.get() << ' ';
    std::cout << std::endl;
    
    return 0;
}
