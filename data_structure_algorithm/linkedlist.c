/*

Generic programming is a way to write functions and data types while making minimal assumptions about the type of data being used. 

typecast => change void ptr to other datatype ptr

void pointer:
see: http://www.geeksforgeeks.org/void-pointer-c/
*/
#include <stdio.h>
#include <stdlib.h>

struct Node
{
	int value;
	// char* details; // ptr is fixed size just like struct Node* => struct could be stored as a sequence in memory
	struct Node* next;
};

struct Node* createFirstNode(int value)
{
	struct Node* new_node = malloc(sizeof(struct Node));
	new_node->value = value;
	new_node->next = NULL;
	return new_node;

};

void addNode(struct Node* head, int value)
{	
	// malloc returns void* => typecast it to any data type ptr
	// if c++ => must explicitly typecast
	// void* ptrs in C are used to implement generic functions
	// void pointers cannot be dereferenced => it indicates how many bytes to read as datatype
	// c standard x allow pointer arithmetic with void pointer => but gcc treat size of void as 1
	struct Node* new_node = (struct Node*)malloc(sizeof(struct Node)); 
	new_node->value = value;
	// new_node->details = details;
	new_node->next = NULL;

	// traverse to the last curr->next == NULL => update curr->next
	struct Node* curr = head;
	while(curr->next != NULL){
		curr = curr->next;
	};
	curr->next = new_node;

};

// TODO: insert front, delete, reverse
void printNode(struct Node* head)
{
	struct Node* curr = head;
	while(curr){
		printf("%d\n", curr->value);
		curr = curr->next;
	}
}

int main(int argc, char const *argv[])
{
	struct Node* head = createFirstNode(2);
	addNode(head, 3);
	printNode(head);

	return 0;
}