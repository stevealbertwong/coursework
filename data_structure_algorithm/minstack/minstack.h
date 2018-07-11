/*
Author: steven wong

stack(linked list implmentation) min()/max() take O(n)
	=> min() O(1)

SOLUTION:
	1. add min field in node
	2. two stacks, one normal, one only store min to the underneath

NOTE:
	1. min range / min of all nodes underneath: 

		node not min that is pushed, min will be nullptr
		but won't be problem since LIFO, it will be popped before 
		current min gets popped

see: bytebybyte max stack
http://www.ritambhara.in/minimum-stack-stack-returning-min-element-in-o1-time/
*/	
#ifndef MIN_STACK_H
#define MIN_STACK_H
#define LOG(x) std::cout << x << std::endl;

#include <iostream>

struct node
{
	int data;
	node *next;
	node *min;
	node(int d, node *nt) : data(d), next(nt){}
};

class MinStack
{
public:
	MinStack(){};
	~MinStack(){};
	void push(int data);
	void pop();
	void minimum();
	void print_stack();

	node *head = nullptr;	
	node *global_min; // O(1)
};

// O(1)
void MinStack::push(int data){
	if(head == nullptr){
		head = new node(data, nullptr);
		head->min = head; // 1st no. always min
		global_min = head;

	// newly pushed node lower than min + point at prev min
	} else if (data < global_min->data){			
		head = new node(data, head);
		head->min = global_min; // point to previous global min
		global_min = head; // update global min

	// nullptr not min, even it might be smaller than previous
	// min, it will be popped before current min gets popped
	} else {		
		head = new node(data, head);
		head->min = nullptr; 
	}
}

// O(1)
void MinStack::pop(){
	if(head == nullptr) return;

	// min of all nodes underneath
	if(head->min != nullptr) global_min = head->min; 
	node *temp = head;		
	head = head->next;	
	delete temp;

}

// O(n) just for testing
void MinStack::minimum(){
	node* temp = head;
	while(temp->next){
		if(temp->min != nullptr){
			LOG(temp->data)
			break;
		}
		temp = temp->next;
	}	
}

// O(n)
void MinStack::print_stack(){
	node *temp = head;
	while(temp){		
		LOG(temp->data)
		temp = temp->next;
	}
}

#endif // MIN_STACK_H