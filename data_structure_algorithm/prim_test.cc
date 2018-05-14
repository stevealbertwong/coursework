/*
g++ -std=c++14 prim_test.cc -o prim_test
*/
#include <iostream>
#include <algorithm>    // std::min_element, std::max_element
#include <vector>
#define LOG(x) std::cout << x << std::endl;

struct edge
{
	char v1;
	char v2;
	int w;
	edge(char ver1, char ver2, int weight):v1(ver1), v2(ver2), w(weight){}
};

struct graph{
	std::vector<char> vertices;
	std::vector<edge> edges; // edge list
	
	// returning all adjacent nodes end node + weight
	std::vector< std::pair<char, int> > adjacent(char v){
		std::vector< std::pair<char, int> > adj_nodes;
		for(auto& edge : edges){
			if(v == edge.v1){
				adj_nodes.push_back(std::make_pair(edge.v2, edge.w));
			}else if(v == edge.v2){
				adj_nodes.push_back(std::make_pair(edge.v1, edge.w));
			}
		}
		return adj_nodes;
	};
};

int main(int argc, char const *argv[])
{
	char t[] = {'a', 'b', 'c', 'd', 'e', 'f'};
	std::vector<char> vertices(t, t + sizeof(t) / sizeof(char));

	std::vector<edge> edges;
	edges.push_back(edge('a','b',4));
	edges.push_back(edge('a','f',2));
	edges.push_back(edge('f','b',3));
	edges.push_back(edge('c','b',6));
	edges.push_back(edge('c','f',1));
	edges.push_back(edge('f','e',4));
	edges.push_back(edge('d','e',2));
	edges.push_back(edge('c','b',3));

	// https://stackoverflow.com/questions/16772477/how-to-get-min-or-max-element-in-a-vector-of-structures-in-c-based-on-some-fi
	edge smallest_edge = *std::min_element(edges.begin(), edges.end(), 
			[&](edge e1, edge e2){return e1.w < e2.w;});
	LOG(smallest_edge.v1)
	LOG(smallest_edge.v2)

	graph g;
	g.edges.push_back(edge('a','b',4));
	g.edges.push_back(edge('a','f',2));
	g.edges.push_back(edge('f','b',3));
	g.edges.push_back(edge('c','b',6));
	g.edges.push_back(edge('c','f',1));
	g.edges.push_back(edge('f','e',4));
	g.edges.push_back(edge('d','e',2));
	g.edges.push_back(edge('c','b',3));
	std::vector< std::pair<char, int> > neigbor_edges = g.adjacent('c');
	for(auto& edge : neigbor_edges){
		LOG(edge.first)
		LOG(edge.second)
	}

	

	return 0;
}