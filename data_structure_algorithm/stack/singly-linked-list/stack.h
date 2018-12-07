#ifndef STACK_H
#define STACK_H
#define LOG(x) std::cout << x << std::endl;

#include <iostream>


class Stack
{
public:
	struct node
	{
		int data;
		node *next;
		node(int d, node *nt) : data(d), next(nt){}
	};
	Stack() : head(nullptr) {};
	~Stack(){};
	void push(int data);
	void pop();
	void max();
	void print_stack();
	void reverse();
private:
	node *head;	
};

/* sol: create 2 more pointers on stack to store prev n next node so could reverse
 spent 4 hours debugging order of pointers -> doon't put prev at first !!!!
 */
void Stack::reverse(){	
	node *cursor = head;
	node *prev;	// where to reverse to 
	node *next_node; // where to advance

	while(cursor){ // break when points to last node, last node's next is null
		next_node = cursor->next;	// store next node so could reverse
		cursor->next = prev;	// reverse
		prev = cursor;	// store prev for next iteration
		cursor = next_node;	// advance
	}

	head = prev;
	
	
	printf("%d\n", head->data);
	printf("%d\n", head->next->data);
	printf("%d\n", head->next->next->data);
	printf("%d\n", head->next->next->next->data);
}

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
	node *node_to_delete = head;	
	head = head->next;
	delete node_to_delete;
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