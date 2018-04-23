/*
tmeplate allows you to amend parameter thru <> without using global var
compile time constant

bo qian intro stl functors



*/

#include <iostream>

using namespace std;

int x = multiplies<int>(3,4) // built in operator

// why not just 2 args or constructor ??
template<int val>
void addVal(int i){
	cout << i + val << endl;
}

int main(int argc, char const *argv[])
{
	std::vector<int> v = {1,2,3,4};
	for_each(v.begin(), v.end(), addVal<2>); // must use constant not var
	return 0;
}