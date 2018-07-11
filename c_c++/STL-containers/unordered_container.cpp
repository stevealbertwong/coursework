/*

https://www.youtube.com/watch?v=NNLvY9O7ufU&t=655s

unordered container:
	=> order of element might change over time
	=> implemented in hash table 
		=> array of linked list
			=> array element: bucket/hash no.
			=> each bucket has a linked list called entries
				to store string hashed to that no.
	=> if fast hash function, 
		=> finding element in hash table is fast
		=> constant time O(1)

hash collision 
	=> not constant amortized search, item hashed to same bucket
	=> degraded unordered containers: O(1) -> O(n)
	=> constant time to linear time

complexity
	=> unordered container: fastest search/insert at any place: O(1)
	=> associative container: binary tree, O(log(n))
	=> vector, deque: O(n)
	=> list: O(1) to insert(given already has ptr at position to insert), O(n) linear time to search

data structure corruption
	=> unorder set/multi-set: 
	=> unorder map/multi-map:

http://www.cplusplus.com/reference/unordered_map/unordered_map/find/

g++ -std=c++11 -o unordered_container unordered_container.cpp

*/

#include <unordered_set>
#include <unordered_map>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

void print_unordered_map(const unordered_map<char, string>& m){
	auto itr = m.find('w');
	if(itr != m.end()){
		// cout << *itr << endl;
		cout << itr->first << endl; // w
		cout << itr->second << endl; // wednesday
	}	
}

int main(int argc, char const *argv[])
{	

	// unordered set
	unordered_set<string> myset = { "red", "green", "blue" };

	// if find() find item, return iter points to that item
	// else, return iterator points to end of container
	// O(1) amortised constant time look up
	unordered_set<string>::const_iterator itr = myset.find("green");

	// dereferencing end iterator is undefined behavior
	if(itr!=myset.end()){
		cout << *itr << endl;
	}

	myset.insert("yellow"); // O(1)

	// insert every item in vector into the set
	vector<string> vec = {"purple", "pink"};
	myset.insert(vec.begin(), vec.end());
	
	unordered_set<string> :: iterator itr2;   
    for (itr2 = myset.begin(); itr2 != myset.end(); itr2++)
        cout << *itr2 << endl;

	// hash table specific api
	// load factor(ratio of total elements and buckets) of hash table =>  0.545455
	cout << "load_factor = " << myset.load_factor() << endl;
	
	string x = "red";
	cout << x << " is in bucket #" << myset.bucket(x) << endl;
	cout << "total bucket #" << myset.bucket_count() << endl;







	// unordered map aka associative array
	unordered_map<char,string> day = {{'m',"monday"},{'t',"tuesday"}};
	cout << day['m'] << endl; // no range check
	cout << day.at('m') << endl; // has range check
	
	// insert in 2 ways
	day['w'] = "wednesday"; // same as insert()
	day.insert(make_pair('f', "friday"));
	
	// cannot be used to modify existing keys in container
	// but can modify existing key's value
	day.insert(make_pair('m', "hello world")); // fail to modify, just nothing happen
	cout << day['m'] << endl; // still monday
	day['m'] = "mondayyyyy"; // succeed
	cout << day['m'] << endl; // mondayyyyyyy
	
	print_unordered_map(day);



	return 0;
}





