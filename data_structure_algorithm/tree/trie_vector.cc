/*
https://codereview.stackexchange.com/questions/160186/a-simple-c-trie-for-working-with-strings
*/
#include <memory>
#include <string>
#include <vector>
// The trie node only has the character it represents and a 
// number of children that come after it
struct MyTrieNode {
    MyTrieNode(const char c) : character(c) {}

    const char character;
    std::vector<MyTrieNode*> children
};
// The actual trie only stores smart pointers to the nodes and the root.
// Furthermore, it is responsible for generation of nodes and search after words
class MyTrie {
public:    

    // Construct with a rootNode that holds no character
    MyTrie() {
        nodes.emplace_back(std::make_unique('\0'));
        rootNode = nodes.back().get();
    }

    // Add a child to a node, only if it is not already there
    MyTrieNode* AddChild(MyTrieNode* node, const char& c) {
        // First search for an existing node
        for (const MyTrieNode* childNode : node->children) {
            if (childNode->character == c) {
                return childNode;  
            }
        }
        // Character not already found so add a new child
        nodes.emplace_back(std::make_unique(c));
        node->children.emplace_back(nodes.back().get());
        return node->children.back();
    }

    // Add a std::string by traversing its characters
    void AddString(const std::string& newString) {
        for (const char& c : newString) {
            AddChild(rootNode, c);
        }
    }

    // Search for a given character in the children of a node or return nullptr
    MyTrieNode* findChild(MyTrieNode* node, const char& c) {
        for (const MyTrieNode* childNode : node->children) {
            if (childNode->character == c) {
                return childNode;  
            }
        }
        return nullptr;
    }

    // Search for a word. Once findChild returns nullptr we can return early as that word is not found
    bool findString(const std::String& word) {
        MyTrieNode* current = rootNode;
        for (const char& c : word) {
            current = findChild(current, c);
            if (current == nullptr) {
                return false;
            }
        }
        return true;
    }
private:
    MyTrieNode* rootNode;
    std::vector<std::unique_ptr<MyTrieNode>> nodes;
}