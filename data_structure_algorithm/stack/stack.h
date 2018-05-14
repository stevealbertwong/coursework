#ifndef STACK_H
#define STACK_H
#define LOG(x) std::cout << x << std::endl;

#include <iostream>

struct node
{
	int data;
	node *next;
	node(int d, node *nt) : data(d), next(nt){}
};

class Stack
{
public:
	Stack(){};
	~Stack(){};
	void push(int data);
	void pop();
	void max();
	void print_stack();
private:
	node *head;	
};

// O(1)
void Stack::push(int data){
	if(head == nullptr){
		head = new node(data, nullptr);
	} else {
		head = new node(data, head);
	}
}

// O(1)
void Stack::pop(){
	if(head == nullptr) return;
	node *temp = head;	
	head = head->next;
	delete temp;
}

// O(n)
void Stack::max(){
	node *temp = head;
	int max = temp->data;	
	while(temp->next){
		temp = temp->next;
		if(temp->data > max){
			max = temp->data;
		}
	}	
}

// O(n)
void Stack::print_stack(){
	node *temp = head;
	while(temp){		
		LOG(temp->data)
		temp = temp->next;
	}
}

#endif // STACK_H