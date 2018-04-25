/*
https://www.youtube.com/watch?v=UTUdhjzws5g&t=6s

lvalue: object that occupies identifiable location in memory (not register)
rvalue: any object that is not lvalue

http://www.bogotobogo.com/cplusplus/C11/4_C11_Rvalue_Lvalue.php

*/

/*
Lvalue example:
(most variables are lvalue)

int i; // lvalue since identifiable address 
int* p = &i;

class dog;
dog d1; // lvalue
*/


/*
Rvalue example:
(e.g. register, function => temporary, destroyed momentarily)

int x = 2; // 2 is rvalue
int x = i + 2; // i + 2 is rvalue
int* p = &(i+2); // error since no memory addr
i+2 = 4; // error, cannot assign different value
2 = i; // error

dog d1;
d1 = dog(); // dog() is rvalue of user defined type class

int sum(int x, int y) {return x+y;}
int i = sum(3,4); // sum(3,4) is rvalue

*/

/*
lvalue reference

int i;
int &r = i; // lvalue ref

int &r = 5; // initialize lvalue ref with rvalue gives error 

// exception: const lvalue ref can be assigned a rvalue
// 2 steps: 1st lvalue created with 5, 2nd r is initialized with temp lvalue
const int& r = 5;


int square(int& x){return x*x;} // takes lvalue ref as arg
square(i); // ok since i is lvalue/ variable
square(40); // error since 40 is rvalue not lvalue

// workaround:
int square(const int& x) {return x*x;} //both square(i) square(40) work

*/



/*
https://www.youtube.com/watch?v=IOkgBrXCtfo


packaged_task + thread
e.g. std::thread t2 = move(t);

http://www.bogotobogo.com/cplusplus/C11/5_C11_Move_Semantics_Rvalue_Reference.php
move() takes an lvalue and converts it into an rvalue

*/

class BoVector{
public:
	// copy constructor: expensive deep copy frm existing object
	BoVector(const BoVector& rhs){ // lvalue reference
		size = rhs.size;
		arr = new double[size];
		for (int i = 0; i < size; ++i) {arr[i] = rhs.arr[i];}		
	}
	// move constructor: inexpensive shallow copy
	BoVector(BoVector&& rhs){
		size = rhs.size;
		arr = rhs.arr;
		rhs.arr = nullptr; // once move, cannot reuse object
	}
	~
private:	
	int size;
	double *arr;
};

void foo(BoVector bv); // called with copy/move constructor
void foo_by_reference(BoVector& bv); // called with no constructor

int main(){
	BoVector bv = createBoVector();
	foo_by_reference(bv); // no constructor called, MOST EFFICIENT
	foo(bv); // copy constructor called, MOST EXPENSIVE
	foo(createBoVector()); // move constructor called
	foo(std::move(bv)); // move constructor called, bv not usable as nullptr, SECOND MOST EFFICIENT


}

