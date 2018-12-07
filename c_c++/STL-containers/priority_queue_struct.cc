/*

g++ -std=c++14 -Wsizeof-array-argument priority_queue_struct.cc -o priority_queue_struct
*/
#include <iostream>
#include <list>
#include <vector>
#include <queue>
#include <algorithm>
#include <stdlib.h>
#include <set>
using namespace std;

struct priorityQueue {
	list<int> path;
	int cost;
	bool operator>(const priorityQueue& rhs) const { return cost > rhs.cost; }
};
class comparison {
public:
	bool operator() (priorityQueue p1, priorityQueue p2) const {
		return (p1 > p2);
	}
};
int main(int argc, char const *argv[])
{
	priority_queue<priorityQueue,vector<priorityQueue>,comparison> pq; // min heap
	priorityQueue pq_node;
	pq_node.path.push_back(1);
	pq_node.path.push_back(2);	
	pq_node.cost = 10;
	pq.push(pq_node);
	int res = pq.top().path.back();
	cout << res << endl;
	if(!pq.empty()){		
		pq.pop();
	}
	return 0;
}