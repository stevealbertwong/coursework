/*
g++ -std=c++11 trie_smart_pointer.cc -o trie_smart_pointer

*/
#include "trie_smart_pointer.h"
using namespace forest::trie;
int main(int argc, char const *argv[]){
	forest::trie::tree t = forest::trie::tree();
	// tree t = tree();
	t.insert("hello");
	std::cout << t.search("hello") << std::endl; // 1
	std::cout << t.search("he") << std::endl; // 0 
	std::cout << t.search("hellp") << std::endl; // 0
	return 0;
}