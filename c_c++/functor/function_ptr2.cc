/*
https://www.youtube.com/watch?v=p4sDgQ-jao4

*/
#include <vector>
#include <iostream>
using namespace std;

// #define LOG(x) cout << x << endl;


void print_nums(vector<int> nums, void (*func)(vector<int> nums)){
	func(nums);

}

void print_func(vector<int> nums){
	for (int num : nums)
	{
		cout << num << endl;
	}

}


int main(int argc, char const *argv[])
{
	vector<int> nums = {1,2,3,4};
	print_nums(nums, print_func); 

	return 0;
}