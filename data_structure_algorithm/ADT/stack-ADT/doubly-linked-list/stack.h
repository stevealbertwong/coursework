#ifndef STACK_H
#define STACK_H
#define LOG(x) std::cout << x << std::endl;
#include <iostream>

struct node
{
	int data;
	node *next; // right
	node *previous; // left
	node(int d, node *nt, node *prv) : data(d), next(nt), previous(prv){}
};

class Stack
{
public:
	Stack() : head(nullptr), tail(nullptr){};
	~Stack(){};
	void push_front(int data);
	void push_back(int data);
	void pop_front();
	void pop_back();
	void reverse();
	void sort_ascend();	
	void max();
	void print_stack();
private:
	node *head;	// leftest
	node *tail;	// rightest
};

void Stack::push_front(int data){
	if(head == nullptr && tail == nullptr){
		head = new node(data, nullptr, nullptr);
		tail = head;
	} else {
		head = new node(data, head, nullptr);
		head->next->previous = head;
	}
}

void Stack::push_back(int data){
	if(head == nullptr && tail == nullptr){
		head = new node(data, nullptr, nullptr);
		tail = head;
	} else {
		tail = new node(data, nullptr, tail);
		tail->previous->next = tail;
	}
}

void Stack::pop_front(){
	if(head == nullptr) return;
	node *temp = head;	
	head = head->next;
	head->previous = nullptr;
	delete temp;
}

void Stack::pop_back(){
	if(head == nullptr) return;
	node *temp = tail;	
	tail = tail->previous;
	tail->next = nullptr;
	delete temp;
}


// O(n)
void Stack::max(){
	// node *temp = head;
	// int max = temp->data;	
	// while(temp->next){
	// 	temp = temp->next;
	// 	if(temp->data > max){
	// 		max = temp->data;
	// 	}
	// }	
}

void Stack::print_stack(){
	node *temp = head;
	while(temp){		
		LOG(temp->data)
		temp = temp->next;
	}
	
	temp = tail;
	while(temp){		
		LOG(temp->data)
		temp = temp->previous;
	}
}

#endif // STACK_H