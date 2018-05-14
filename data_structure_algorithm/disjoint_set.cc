/*
boqian

disjoint set
	=> chained tgt unordered map's key value
	=> recursively find chained map's root

1. constructor 
		unordered_map i.e. hashtable to replace pointer
2. union()
		chaining unordered_map
3. root()
		if any 2 nodes have same root => belong to same set
		base case: root must point at itself

*/

class Disjoint_Set{
	unordered_map<char, char> parent;
public: 
	Disjoint_Set(char[] keys){
		for(char& key : keys){
			parent[key] = key; // all seperate sets
		}
	}

	char root(char v){
		// base case: root must point at itself
		if(parent[v] == v){
			return v;
		}else{
			// recursively search for root
			return root(parent[v]);
		}
	}

	// join root
	void union(char v1, char v2){
		char r1 = root(v1);
		char r2 = root(v2);
		parent[r1] = r2;
	}	
};


int main(int argc, char const *argv[])
{
	Disjoint_Set ds({'a', 'b', 'c', 'd', 'e'});

	return 0;
}