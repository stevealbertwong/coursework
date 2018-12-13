/*
https://www.techiedelight.com/cpp-implementation-trie-data-structure/

*/
#include <iostream>
#define CHAR_SIZE 128

class Trie{
public:	
	Trie(){
		this->isLeaf = false;

		for (int i = 0; i < CHAR_SIZE; i++)
			this->character[i] = nullptr;
	}

	void insert(std::string);
	bool deletion(Trie*&, std::string);
	bool search(std::string);
	bool haveChildren(Trie const*);

	// KEY DATA STRUCTURE
	Trie* character[CHAR_SIZE];	// char* stores child tries
	bool isLeaf;
};

// for loop insert a key in the Trie
void Trie::insert(std::string key){	
	Trie* curr = this; // start from root node
	for (int i = 0; i < key.length(); i++){
		// create a new node if path doesn't exists
		if (curr->character[key[i]] == nullptr)
			curr->character[key[i]] = new Trie();
		
		curr = curr->character[key[i]]; // update curr as child node
	}	
	curr->isLeaf = true; // mark current node as leaf
}

// for loop 
bool Trie::search(std::string key){	
	if (this == nullptr) // false if Trie is empty
		return false;

	Trie* curr = this; // root
	for (int i = 0; i < key.length(); i++){	// compare trie node w string
		curr = curr->character[key[i]]; // go to child node
		
		if (curr == nullptr) // trie does not contain trie
			return false;
	}
	return curr->isLeaf;
}

// helper to delete()
bool Trie::haveChildren(Trie const* curr){
	for (int i = 0; i < CHAR_SIZE; i++)
		if (curr->character[i])
			return true;	// child found
	return false;
}

// recursively delete a key
bool Trie::deletion(Trie*& curr, std::string key){
	// return if Trie is empty
	if (curr == nullptr)
		return false;

	// if we have not reached the end of the key
	if (key.length()){
		// recurse for the node corresponding to next character in the key
		// and if it returns true, delete current node (if it is non-leaf)

		if (curr != nullptr &&
			curr->character[key[0]] != nullptr &&
			deletion(curr->character[key[0]], key.substr(1)) &&
			curr->isLeaf == false)
		{
			if (!haveChildren(curr))
			{
				delete curr;
				curr = nullptr;
				return true;
			}
			else {
				return false;
			}
		}
	}

	// if we have reached the end of the key
	if (key.length() == 0 && curr->isLeaf){
		// if current node is a leaf node and don't have any children
		if (!haveChildren(curr))
		{
			// delete current node
			delete curr;
			curr = nullptr;

			// delete non-leaf parent nodes
			return true;
		}

		// if current node is a leaf node and have children
		else
		{
			// mark current node as non-leaf node (DON'T DELETE IT)
			curr->isLeaf = false;

			// don't delete its parent nodes
			return false;
		}
	}

	return false;
}

// C++ implementation of Trie Data Structure
int main()
{
	Trie* head = new Trie();

	head->insert("hello");
	std::cout << head->search("hello") << " ";  	// print 1

	head->insert("helloworld");
	std::cout << head->search("helloworld") << " "; // print 1

	std::cout << head->search("helll") << " ";  	// print 0 (Not found)

	head->insert("hell");
	std::cout << head->search("hell") << " ";   	// print 1

	head->insert("h");
	std::cout << head->search("h"); 				// print 1

	std::cout << std::endl;

	head->deletion(head, "hello");
	std::cout << head->search("hello") << " ";  	// print 0

	std::cout << head->search("helloworld") << " "; // print 1
	std::cout << head->search("hell");  			// print 1

	std::cout << std::endl;

	head->deletion(head, "h");
	std::cout << head->search("h") << " ";  		// print 0
	std::cout << head->search("hell") << " ";   	// print 1
	std::cout << head->search("helloworld");		// print 1

	std::cout << std::endl;

	head->deletion(head, "helloworld");
	std::cout << head->search("helloworld") << " "; // print 0
	std::cout << head->search("hell") << " ";   	// print 1

	head->deletion(head, "hell");
	std::cout << head->search("hell");  			// print 0

	std::cout << std::endl;

	if (head == nullptr)
		std::cout << "Trie empty!!\n";  			// Trie is empty now

	std::cout << head->search("hell");  			// print 0

	return 0;
}