/*
https://www.youtube.com/watch?v=nU18p75u1oQ&t=18s

callable obejct == functor == function == lambda
also applicable
	=> async()
	=> bind()
	=> called_once()
*/
#include <thread>
#include <utility>
#include <iostream>
using namespace std;

class A{
public:
	void f(int x, char c){}
	long g(double x){return 0;}
	int operator()(int n) {
		cout << n*n << endl;
		return n*n;
	}
};

int foo(int x){return x*x;}

int main(int argc, char const *argv[])
{
	A a;

	// thread t1(a, 6); // creates copy of a, invoked as functor
	// thread t2(ref(a), 6); // reference of a as functor
	// thread t3(A(), 6); // creates temp A, temporary A moved into thread object
	// thread t4([](int x){return x*x;}, 6);
	// thread t5(foo, 6);
	// thread t6(&A::f, a, 8, 'w'); // making copy of a, invoke A's f function(8,'w') as args
	// thread t7(&A::f, &a, 8, 'w'); // a, invoke A's f function(8,'w') as args
	
	// move a from current to child thread
	// a no longer usable in main thread
	thread t8(move(a), 6); 

	t8.join(); // rmb to join t, otherwise crash

	return 0;
}