class stack
{
public:
	struct node{
		int value;
		node *next; 
	};
	node *head;
	init();
	~test();
	push(int value);
	pop();
};

void init(){
	head = new node();
}

void push(int value){
	node *new_head = new node();
	new_head->next = head;
	head = new_head;
	head->value = value;
}

int pop(){
	int popped_value = head->value;
	node *old_head = head;
	head = head->next;	
	delete old_head; 
	return popped_value;
}

int main(int argc, char const *argv[])
{
	stack s = stack()
	s.init();


	return 0;
}