/*

*/

std::deque<packaged_task<int()>> task_q;
std::mutex mu;
std::condition_variable cv;


void slave(){

	// lock for both cv n task_q
	

	// predicate/condition lambda
	// internally acquires mutex to check if predicate met 
	// if predicate not true, release lock n wait for signal again
	cv.wait();
}

int factorial(int n){
	int sum = 1;
	for (int i = n; i > 0; --i)
	{
		sum *= i;	
	}
	cout << sum << endl;
	return sum;
}

int main(int argc, char const *argv[])
{
	std::thread t1(slave);
	std::packaged_task<int()> t(std::bind(factorial, 6));
	std::future fu = t.get_feture();

	fu.get(); // wait till packaged_task done executes i.e. t()

	return 0;
}