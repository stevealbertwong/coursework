/*

 unordered map -> random order
2 : 1500
1 : 1
3 : 5
9 : 200
20 : 2
5 : 10
 ordered map -> ordered by key's value 
1 : 2
2 : 1
3 : 78
5 : 50
20 : 100

https://thispointer.com/map-vs-unordered_map-when-to-choose-one-over-another/
https://www.geeksforgeeks.org/map-vs-unordered_map-c/

g++ -std=c++11 unordered_map.cc -o unordered_map 
*/
#include <string>
#include <map>
#include <unordered_map>
#include <iostream>

using namespace std;

int main() 
{ 
    std::cout <<  " unordered map -> random order" << '\n';     
    std::unordered_map<int, int> unorder;       
    unorder[5] = 10; 
    unorder[3] = 5; 
    unorder[20] = 100; 
    unorder[1] = 1; 
    unorder[2] = 1500; 
    unorder[9] = 200; 
    unorder[20] = 100; // duplicate
    unorder[20] = 2; // update value         
    for (auto i = unorder.begin(); i != unorder.end(); i++) { 
        std::cout << i->first << " : " << i->second << '\n'; 
    } 

    std::cout <<  " ordered map -> ordered by key's value " << '\n';       
    std::map<int, int> order;       
    order[5] = 50; 
    order[3] = 78; 
    order[20] = 100; 
    order[1] = 2; 
    order[2] = 1;     
    for (auto i = order.begin(); i != order.end(); i++) { 
        std::cout << i->first << " : " << i->second << '\n'; 
    } 

} 