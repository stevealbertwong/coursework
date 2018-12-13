/**
 * @file trie.h

 https://codereview.stackexchange.com/questions/191205/trie-data-structure-implementation-in-c11-using-smart-pointers
 https://github.com/xorz57/forest


 */

#ifndef TRIE_H
#define TRIE_H
#include <iostream>
#include <string>
#include <memory>
#define ALPHABET_SIZE 26
namespace forest {
  namespace trie {

    struct node {
      node() {
        this->end = false; 
        for (int i = 0; i < ALPHABET_SIZE; i++) {
          this->children[i] = NULL;}}

      std::shared_ptr<node> children[ALPHABET_SIZE];
      bool end; // storing "hello" =/= "hell" or "he" 
    };

    class tree {
      private:
        std::shared_ptr<node> root;
      public:
        
        tree() {root = std::make_shared<node>();}
        
        void insert(const std::string &key) {
          std::shared_ptr<node> n = root;
          for (int i = 0; i < key.length(); i++) {
            int index = key[i] - 'a';
            if (n->children[index] == nullptr) {
              n->children[index] = std::make_shared<node>();
            }
            n = n->children[index];
          }
          n->end = true;
        }

        const bool search(const std::string &key) {
          std::shared_ptr<node> n = root;
          for (int i = 0; i < key.length(); i++) {
            int index = key[i] - 'a';
            if (n->children[index] == nullptr) {
              return false;}
            n = n->children[index];
          }
          return (n != nullptr && n->end == true);
        }
    };
  }
}

#endif