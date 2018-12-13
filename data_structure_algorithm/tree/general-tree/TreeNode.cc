#include "TreeNode.h"
#include <string>
#include <vector>
#include <iostream>

TreeNode::TreeNode() {};

TreeNode::TreeNode(std::string iTextContent, std::string iTagName) :
    textContent(iTextContent),	// std::string textContent;        
    tagName(iTagName),	// std::string tagName;
    parent(NULL){} 

/************* Add a child to general tree at any node **********/
void TreeNode::setParent(TreeNode *theParent){
    parent = theParent;} // child node points to parent node

// update BOTH parent n child TreeNode private variables
void TreeNode::appendChild(TreeNode *child){
    child->setParent(this); // this refers to TreeNode *parent;
    children.push_back(child);} // vector<TreeNode *> children;   

/******** Recursion traverse general tree at any node*************/
TreeNode* TreeNode::getChild(int pos){   
    if(children.size() < pos) // vector<TreeNode *> children;
        return NULL;
    else
        return children[pos];}

int TreeNode::countNodesRec(TreeNode *root, int& count){   
    TreeNode *parent = root; // treat calling node as parent 
    TreeNode *child = NULL;

    for(int it = 0; it < parent->childrenNumber(); it++){   
        child = parent->getChild(it); // vector random access
        count++;        
        if(child->childrenNumber() > 0){   
            countNodesRec(child, count);}}
    return count;}

int TreeNode::grandChildrenNum(){  
    int t = 0;
    if(children.size() < 1){
        return 0;}
    countNodesRec(this, t);	// this == node->grandChildrenNum();
    return t;}

void TreeNode::removeChild(int pos){   
    if(children.size() > 0) {
        children.erase(children.begin()+ pos);}
    else {
        children.pop_back();}}




/* getter, setter */

void TreeNode::popBackChild()
{
    children.pop_back();
}



bool TreeNode::hasChildren()
{
    if(children.size() > 0)
        return true;
    else
        return false;
}

bool TreeNode::hasParent()
{
    if(parent != NULL)
        return true;
    else 
        return false;
}

TreeNode * TreeNode::getParent()
{
    return parent;
}

int TreeNode::childrenNumber()
{
    return children.size();
}

std::string TreeNode::getTextContent()
{
    return textContent;
}

std::string TreeNode::getTagName()
{
    return tagName;
}