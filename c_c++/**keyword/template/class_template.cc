/*

when defining function member outside declaration of the class

passing param of data type to a class
https://www.youtube.com/watch?v=U2QvTsMvWmM

https://www.youtube.com/watch?v=8kjVFp-Y4GA


*/

// function defined outside the class prototype's
// template parameters is same as the class prototype

#include <iostream>
// T: unknown data types to be substituted
template <typename T>
class Compare{

private:
	T first_num, second_num;
public:
	// constructor
	Compare(T a, T b){
		first_num = a;
		second_num = b;
	}

	T bigger(); // T is return type of bigger()
};

// function member outside declaration of class template
// <T>: class template param same as class Compare
template <typename T>
T Compare<T>::bigger(){
	return (first_num>second_num?first_num:second_num);
}


int main(int argc, char const *argv[])
{
	Compare<int> comp(1,3);
	int num = comp.bigger();
	std::cout << num << std::endl;

	return 0;
}

