#ifndef LIB_STRING_H
#define LIB_STRING_H


/* typedef almost same as struct 
=> use typedef so cant be overwritten by function 

uint32_t instead of int => document your thought

double struct linked list => access through [] instead of ->next
=> not as easy to insert/delete ??

*/
typedef struct {
	char *label;
	uint32_t addr;
} Symbol;

typedef struct {
	Symbol* sym; // keep realloc to expand as linked list
	uint32_t symbol_count;
	uint32_t max_cap;
} SymbolTable;

/*
read file parse it into tokens
*/
void read_tokens(char* filename);



#endif