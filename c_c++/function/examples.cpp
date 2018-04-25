/*
c++ lambda function
https://www.youtube.com/watch?v=uk0Ytomv0wY&t=260s

*/


/* packaged_task: http://thispointer.com/c11-multithreading-part-10-packaged_task-example-and-tutorial/
 * Function Object to Fetch Data from DB

 http://thispointer.com/c11-multithreading-part-9-stdasync-tutorial-example/

 */
struct DBDataFetcher
{
    std::string operator()(std::string token)
    {
        // Do some stuff to fetch the data
        std::string data = "Data From " + token;
        return data;
    }
};


struct DataFetcher
{
    std::string operator()(std::string recvdData)
    {
        // Make sure that function takes 5 seconds to complete
        std::this_thread::sleep_for (seconds(5));
        //Do stuff like fetching Data File
        return "File_" + recvdData;
 
    }
}; 
//Calling std::async with function object
std::future<std::string> fileResult = std::async(DataFetcher(), "Data");




std::future<std::string> resultFromDB = std::async([](std::string recvdData){
 
                        std::this_thread::sleep_for (seconds(5));
                        //Do stuff like creating DB Connection and fetching Data
                        return "DB_" + recvdData;
 
                    }, "Data");



/*
https://stackoverflow.com/questions/22332181/passing-lambdas-to-stdthread-and-calling-class-methods
*/

auto functor = 
   [this](const Cursor& c, size_t& result) ->void {result = classMethod(c);};
size_t a;
Cursor cursor = someCursor();
std::thread t1([&] {a = classMethod(cursor);});
// std::thread t1(functor, std::ref(cursor), std::ref(a)) // same
t1.join();


/*
vitvit threadpool
*/
template<typename F, typename... Rest>
auto push(F && f, Rest&&... rest) ->std::future<decltype(f(0, rest...))> {
    auto pck = std::make_shared<std::packaged_task<decltype(f(0, rest...))(int)>>(
        std::bind(std::forward<F>(f), std::placeholders::_1, std::forward<Rest>(rest)...)
    );
    // function wrap lambda ??
    auto _f = new std::function<void(int id)>([pck](int id) {
        (*pck)(id);
    });
    this->q.push(_f);

    std::unique_lock<std::mutex> lock(this->mutex);
    this->cv.notify_one();

    return pck->get_future();
}

/* threadpool crytek
*/
void operator()() {
  std::function<void()> func;
  bool dequeued;
  // class inside class's variables ??
  while (!m_pool->m_shutdown) {
    {
      std::unique_lock<std::mutex> lock(m_pool->m_conditional_mutex);
      if (m_pool->m_queue.empty()) {
        m_pool->m_conditional_lock.wait(lock);
      }
      dequeued = m_pool->m_queue.dequeue(func);
    }
    if (dequeued) {
      func();
    }
  }
}






// funcVar: function pointer, assign variable to a function with no name
// []: capture list/closure, using existing outside variable inside function
// (int a, int b): parameter list
// -> int: return type, optional when return type is obvious
auto funcVar[](int a, int b) -> int{
	// body of the function
};

// takes no para, returns void
auto sayHello = [](){cout << "hello" << endl};
sayHello();

// 
auto product = [](int x, int y) -> int {return x * y;};
product(7,19)


// cs110 scheduler.cc
void HTTPProxyScheduler::scheduleRequest(int connectionfd, const string& clientIPAddress) {
	pair<int, const string> p = make_pair(connectionfd, clientIPAddress);
	workers.schedule([this, p] {
		handler.serviceRequest(p);
	});

}

// cs110 threadpool.cc
thread dt([this]() -> void { 
	this->dispatcher();
}); 
dt.detach();



thread wt([this](size_t num_active_threads) -> void {
	this->worker(num_active_threads);
}, num_active_threads); // thread's 2nd arg is parameter to pass in threaded function
wt.detach(); // worker thread will live forever since while(true) + no waiting/thread.join here




// Jakob Progsch, NVIDIA threadpool.h
template<class F, class... Args>
auto ThreadPool::enqueue(F&& f, Args&&... args) 
    -> std::future<typename std::result_of<F(Args...)>::type>
{
    using return_type = typename std::result_of<F(Args...)>::type;

    auto task = std::make_shared< std::packaged_task<return_type()> >(
            std::bind(std::forward<F>(f), std::forward<Args>(args)...)
        );
        
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



// Mariano game engine CRYTEK, threadpool.h
template<typename F, typename...Args>
auto submit(F&& f, Args&&... args) -> std::future<decltype(f(args...))> {
	// Create a function with bounded parameters ready to execute
	std::function<decltype(f(args...))()> func = std::bind(std::forward<F>(f), std::forward<Args>(args)...);
	// Encapsulate it into a shared ptr in order to be able to copy construct / assign 
	auto task_ptr = std::make_shared<std::packaged_task<decltype(f(args...))()>>(func);

	// Wrap packaged task into void function
	std::function<void()> wrapper_func = [task_ptr]() {
	  (*task_ptr)(); 
	};

	// Enqueue generic wrapper function
	m_queue.enqueue(wrapper_func);

	// Wake up one thread if its waiting
	m_conditional_lock.notify_one();

	// Return future from promise
return task_ptr->get_future();
}






// PID controller udacity
h.onMessage([&pid](uWS::WebSocket<uWS::SERVER> ws, char *data, size_t length, uWS::OpCode opCode) {
    // "42" at the start of the message means there's a websocket message event.
    // The 4 signifies a websocket message
    // The 2 signifies a websocket event
    if (length && length > 2 && data[0] == '4' && data[1] == '2') {
        auto s = hasData(std::string(data).substr(0, length));
        if (s != "") {
            auto j = json::parse(s);
            std::string event = j[0].get<std::string>();
            if (event == "telemetry") {
                // j[1] is the data JSON object
                double cte = std::stod(j[1]["cte"].get<std::string>());
                double speed = std::stod(j[1]["speed"].get<std::string>());
                double angle = std::stod(j[1]["steering_angle"].get<std::string>());
                double steer_value;

                pid.UpdateError(cte);

                steer_value = pid.TotalError();

                // DEBUG
                std::cout << "CTE: " << cte << " Steering Value: " << steer_value << std::endl;

                json msgJson;
                msgJson["steering_angle"] = steer_value;
                msgJson["throttle"] = 0.4;
                auto msg = "42[\"steer\"," + msgJson.dump() + "]";
                std::cout << msg << std::endl;
                ws.send(msg.data(), msg.length(), uWS::OpCode::TEXT);
            }
        } else {
            // Manual driving
            std::string msg = "42[\"manual\",{}]";
            ws.send(msg.data(), msg.length(), uWS::OpCode::TEXT);
        }
    }
}




