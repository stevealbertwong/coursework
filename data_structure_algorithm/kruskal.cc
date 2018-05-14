/*
boqian

1. data structure
		path
		disjoint set(vertices cluster) => tree based disjoint sets
		queue of map<v1 v2, weight> sort by ascending weight
2. for each map<v1 v2, weight> 
		if v1 v2 not in same disjoint i.e. not same root
			add as path !!
			union v1 n v2 root

struct vs class
	=> same except class default private
	=> inheritance, operator overloading(struct defines method)
	=> struct exists to maintain backward compatiability w c

disjoint set(chain + root) applied on graph
	=> clusters keep merging until formed one cluster
*/

struct edge
{
	char v1;
	char v2;
	int w;
	edge(char ver1, char ver2, int weight):v1(ver1), v2(ver2), w(weight){}
};

struct graph{
	std::vector<char> vertices;
	std::vector<edge> edges;
};

void kruskal(){
	sort(e);
	for(e : e){
		if(root(e.v1)!=root(e.v2)){
			union()
			path.add(e)
		} 
	}
}

int main(int argc, char const *argv[])
{
	char t[] = {'a', 'b', 'c', 'd', 'e', 'f'};
	graph g;
	// iterator constructor
	g.v = std::vector<char>(t, t + sizeof(t)/sizeof(t[0]));
	g.edges.push_back(edge('a', 'b', 4));
	
	return 0;
}