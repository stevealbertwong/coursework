/*
https://codereview.stackexchange.com/questions/199643/simple-trie-class-in-c

https://codereview.stackexchange.com/questions/173451/trie-implementation-in-c
*/
#include <unordered_map>
#include <iostream>
#include <string>
#include <vector>

class Node {
    private:  // KEY DATA STRUCTURE
        std::unordered_map<char, Node*> mchildren;
        bool is_complete_word; // left node
        char mcontent;
    public:
        std::unordered_map<char, Node*> children() { return mchildren; }
        Node *find_child(char c);
        void complete() { is_complete_word = true; }
        void not_complete() { is_complete_word = false; }
        bool is_complete() { return is_complete_word; }
        void set_content(char c) { mcontent = c; }
        char content() { return mcontent; }
        void add_child(Node *n) { mchildren[n->content()] = n; }
        bool has_children() { return !mchildren.empty(); }
        Node() { 
            is_complete_word = false;
            mcontent = ' ';
        }
};

class Trie {
    private:
        Node *root;
    public:
        void add_word(std::string s);
        bool search_word(std::string s);
        void delete_word(std::string s);
        Trie();
};

Trie::Trie() {
    root = new Node();
}

bool delete_until(Node *node, std::string s, size_t level, size_t len) {
    if(node != NULL) {
        if( level == len) {
            if(node->is_complete()) {
                node->not_complete();
                if(!node->has_children()) {
                    return true;
                }
                return false;
            }
        } else {
            if(delete_until(node->find_child(s.at(level)), s, level + 1, len))
            {
                delete node->find_child(s.at(level));
                return ( !node->is_complete() && !node->has_children());
            }
        }
    }

    return false;
}
void Trie::delete_word(std::string s) {

    Node *rt = root;
    size_t len = s.size();
    if(len > 0) {
        delete_until(rt, s, 0, len);
    }
}



Node *Node::find_child(char c) {
    if(mchildren.find(c) != mchildren.end())
        return mchildren[c];
    return NULL;
}

void Trie::add_word(std::string s) {
    Node *current = root;
    if(s.length() == 0) {
        current->complete();
        return;
    }
    for(size_t i = 0; i < s.length(); ++i) {
        Node *child = current->find_child(s[i]);
        if(child != NULL) { 
            std::cout << "child != NULL" << " word = " << s << std::endl;
            current = child; }
        else if (child == NULL) {
            std::cout << "child = NULL" << " word = " << s << std::endl;
        Node *tmp = new Node();
        tmp->set_content(s[i]);
        current->add_child(tmp);
        current = tmp;
        }
        if(i == s.length() - 1)
            current->complete();
    }
}

bool Trie::search_word(std::string s)
{
    Node* current = root;

    while ( current != NULL )
    {
        for ( size_t i = 0; i < s.length(); i++ )
        {
            Node* tmp = current->find_child(s[i]);
            if ( tmp == NULL )
                return false;
            current = tmp;
        }

        if ( current->is_complete() )
            return true;
        else
            return false;
    }

    return false;
}

int main() {

    Trie *t = new Trie();
    t->add_word("tes");
    t->add_word("test");
    t->add_word("testy");
    t->add_word("Hello");

    if(t->search_word("Hello")) { std::cout << "found Hello" <<std::endl;}
    t->delete_word("Hello");
    if(!t->search_word("Hello")) { std::cout << "Hello gone" <<std::endl;}
    if(t->search_word("test")) { std::cout << "found test" <<std::endl;}
    t->delete_word("test");
    if(!t->search_word("test")) { std::cout << "test gone" <<std::endl;}
    if(t->search_word("testy")) { std::cout << "found testy" <<std::endl;}
    return 0;
}