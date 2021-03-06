/*
https://www.geeksforgeeks.org/operator-overloading-cpp-print-contents-vector-map-pair/
*/
// C++ program to print vector objects
// by overloading "<<" operator
#include <iostream>
#include <vector>
using namespace std;
 
// C++ template to print vector container elements
template <typename T>
ostream& operator<<(ostream& os, const vector<T>& v)
{
    os << "[";
    for (int i = 0; i < v.size(); ++i) {
        os << v[i];
        if (i != v.size() - 1)
            os << ", ";
    }
    os << "]\n";
    return os;
}
 
// Driver code
int main()
{
    vector<int> vec{ 4, 2, 17, 11, 15 };
 
    // Printing the elements directly
    cout << vec;
    
    return 0;
}