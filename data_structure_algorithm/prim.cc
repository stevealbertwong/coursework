/*
edge list graph implementation

1. pick edge with smallest link + use that end vertex as start
2. store as path
3. find all adjacent nodes of incremental tree w new vertex
4. update edge, weight map

*/

#include <iostream>
#include <algorithm>    // std::min_element, std::max_element
#include <vector>
#include <unordered_map>
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

void prim(graph& g){
	std::unordered_map<char, char> PATH;	
	std::unordered_map<char, std::pair<char, int>> PRIM_SCORE; // candidate nodes's parent n weight
	std::vector< std::pair<char, int> > neigbor_edges;
	
	std::vector<char> vertices_copy = g.vertices;

	for(char vc : vertices_copy){		
		PRIM_SCORE[vc] = std::make_pair('\0', INT_MAX); // NULL parent, infinite weight
	}
	
	// start w lowest weight node from edges
	edge smallest_edge = *std::min_element(g.edges.begin(), g.edges.end(), 
			[&](edge e1, edge e2){return e1.w < e2.w;});
	char curr_node = smallest_edge.v1;
	PRIM_SCORE[curr_node] = std::make_pair(curr_node, 0);
	

	while(!vertices_copy.empty()){
		
		// from all candidate node, pick lowest cost/prim score
		char candidate_node = *std::min_element(vertices_copy.begin(), vertices_copy.end(), 
			[&](char v1, char v2){return PRIM_SCORE[v1].second < PRIM_SCORE[v2].second;});

		// remove + erase nodes
		std::vector<char>::iterator remove_itr = remove(vertices_copy.begin(), 
			vertices_copy.end(), candidate_node);
		vertices_copy.erase(remove_itr, vertices_copy.end());

		// record path key:child, value:parent
		PATH[candidate_node] = PRIM_SCORE[candidate_node].first;

		// update prim score of all neigbour nodes
		neigbor_edges = g.adjacent(candidate_node);
		for(auto& neigbor_edge : neigbor_edges){
			if(neigbor_edge.second < PRIM_SCORE[neigbor_edge.first].second){
				// candidate nodes's parent n weight
				PRIM_SCORE[neigbor_edge.first] = std::make_pair(candidate_node, neigbor_edge.second);
			}
		}
		curr_node = candidate_node;
	}
	LOG("EXAM")
	for(auto& p : PATH){
		LOG(p.first)
		LOG(p.second)
		LOG('\n')
	}

	LOG("prim score")
	for(auto& ps : PRIM_SCORE){
		LOG(ps.first)
		LOG(ps.second.first)
		LOG(ps.second.second)
		LOG('\n')
	}
}	

int main(int argc, char const *argv[])
{
	graph g;

	char t[] = {'a', 'b', 'c', 'd', 'e', 'f'};
	g.vertices = std::vector<char> (t, t + sizeof(t) / sizeof(char));
	
	g.edges.push_back(edge('a','b',4));
	g.edges.push_back(edge('a','f',2));
	g.edges.push_back(edge('f','b',3));
	g.edges.push_back(edge('c','b',6));
	g.edges.push_back(edge('c','f',1));
	g.edges.push_back(edge('f','e',4));
	g.edges.push_back(edge('d','e',2));
	g.edges.push_back(edge('c','d',3));
	prim(g);

	return 0;
}