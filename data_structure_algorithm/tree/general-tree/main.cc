/*
https://codereview.stackexchange.com/questions/135432/c-tree-class-implementation

implement a class for the Node of a Tree in C++ in order to represent an HTML structure


g++ -std=c++14 TreeNode.cc main.cc -o tree

## to create more warning lol
g++ -std=c++14 -Wall -Wextra -pedantic TreeNode.cc main.cc -o tree
*/

#include <iostream>
#include <vector>
#include "TreeNode.h"

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char** argv) {

    TreeNode *itr = NULL;

    TreeNode *node = new TreeNode("k", "p");
    node->appendChild(new TreeNode("test1", "testag"));
    node->appendChild(new TreeNode("test2", "testag"));
    node->appendChild(new TreeNode("test3", "testag"));

    itr = node->getChild(0);

    itr->appendChild(new TreeNode("test1a", "testtag"));
    itr->appendChild(new TreeNode("test1b", "testtag"));
    itr->getChild(0)->appendChild(new TreeNode("test1aa", "testtag"));

    itr = node->getChild(1);
    itr->appendChild(new TreeNode("test2a", "testtag"));
    itr->appendChild(new TreeNode("test2b", "testtag"));

    itr->getChild(0)->appendChild(new TreeNode("test2aa", "testtag"));

    std::cout<<node->grandChildrenNum();

    return 0;
}