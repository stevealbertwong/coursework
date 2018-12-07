#ifndef STACK_H
#define STACK_H
#define LOG(x) std::cout << x << std::endl;
#include <iostream>
struct node{
	node *next;
	node(int d, node *nt) : data(d), next(nt){}
};
class Stack{
public:
	Stack() : head(nullptr) {};
	~Stack(){};
	void push(int data);
private:
	node *head;};
#endif // STACK_H



