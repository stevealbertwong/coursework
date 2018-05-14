/*
CtCI 4.1 route between nodes

adjacency list graph implementation

g++ -std=c++14 graph.cc -o graph

*/

#include <iostream>
#include <vector>
using namespace std;

class Graph
{
public:
	int V;	// number of vertices
	vector<vector<int> > adj;  //adjacency list 

	Graph(int V);
	void addEdge(int x, int y);
	bool isRoute(int x, int y);
};

// Constructor
Graph::Graph(int V)
{
	this->V=V;

	// initialize 2D => push back extra element
	// vector<vector<int> > adja(6, vector<int>(6)); 
	
	// init 1D
	vector<vector<int> > adja(6); 
	this->adj = adja;
}


void Graph::addEdge(int x, int y){

	adj[x].push_back(y);
}


std::ostream& operator<<(std::ostream & stream, const Graph& graph){
	for (int j = 0; j < 6; ++j)
	{	
		std::vector<int>::const_iterator i;
		for (i = graph.adj[j].begin(); i != graph.adj[j].end(); ++i){
			stream << *i << ' ';
		}
		stream << '\n';
	}

	return stream;
}

int main(){
	
    Graph g(6);	
    g.addEdge(5, 2);
    g.addEdge(5, 0);
    g.addEdge(4, 0);
    g.addEdge(4, 1);
    g.addEdge(2, 3);
    g.addEdge(3, 1);

/*	
	Test graph :

	0 <---4---->1
	^ 			^
	|			|
	|			|
    5---->2---->3 

*/
    cout << g;

    return 0;
}