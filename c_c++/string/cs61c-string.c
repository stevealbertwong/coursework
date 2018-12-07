/*


e.g. readlines() 
=> read a file return array of string

e.g. readtokens()
=> read a file return array of tokens

*/


#include <stdio.h>
#include <string.h>
#include <stdlib.h>


/************************************************************************************************
see: https://stackoverflow.com/questions/8164000/how-to-dynamically-allocate-memory-space-for-a-string-and-get-that-string-from-u
*************************************************************************************************/

// char *dynamic_string()
// {
//     char *line = NULL, *tmp = NULL;
//     size_t size = 0, index = 0;
//     int ch = EOF;

//     while (ch) {
//         ch = getc(stdin); 

//         /* Check if we need to stop. */
//         if (ch == EOF || ch == '\n')
//             ch = 0;

//         /* Check if we need to expand. */
//         if (size <= index) {
//             size += CHUNK;
//             tmp = realloc(line, size);
//             if (!tmp) {
//                 free(line);
//                 line = NULL;
//                 break;
//             }
//             line = tmp;
//         }

//         /* Actually store the thing. */
//         line[index++] = ch;
//     }

//     return line;
// }





/************************************************************************************************

void read_tokens(char *filename){

  FILE *f = fopen(filename, "r");
  char line[1000];
  int c; // c is int since EOF is negative number and char is unsigned
  int n =0;

  while((c=getc(f))!= EOF){
    //putchar(c); // write char to stdout + faster than printf
    //if(c == '\n') printf("line break"); // if "n" there will be string literal use strcmp error
    line[n] = c;
    n++;
    if(c=='\n') {
      line[n+1] = '\0'; // null terminate string otherwise undefined behavior
      //printf("%s", line);      
      
      // strtok_ptr points at the string tokens      
      char* strtok_ptr = strtok(line, " ");
      while(strtok_ptr!=NULL){
        printf("%s\n", strtok_ptr);        
        strtok_ptr = strtok(NULL, " ");
      }
      
      n = 0;
      memset(line, 0, sizeof(line)); // ** READ MEMSET zeor entire string up till null character, strlen(line)=>werid print 
      //strcpy(line,""); // empty string  
      //line[0] = '\0';     
    }
  }
}

*************************************************************************************************/




/************************************************************************************************

1. malloc both symboltable and symbol
2. traverse and updates linked list 

NOTE: 
char *s1= malloc(sizeof(char)) vs char s1[10] = "string" vs char *s1 = "string" 
if declared char* instead of char[] e.g. struct contains char* 
=> cant initialize let alone access 
=> only save is malloc => malloc converts char* to char[]
=> malloc is your good friend and saves your ass if char* s1;

strcpy does not work on char *s1 = "string" but what about malloc ??? => malloc you could [] to traverse
see: http://www.cs.fsu.edu/~myers/cop3330/examples/strings/strcpy.txt
when typecast ??
double struct[] linked list vs vanilla linked list ??
dict = traversing linked list

why .label instead of ->label ??

*************************************************************************************************/


/************************************************************************************************


SymbolTable* create_label_table_61cAssembler(){
    SymbolTable *label_table = malloc(sizeof(struct SymbolTable));
    Symbol *label_table->sym = malloc(sizeof(struct Symbol, MAX_CAP)); // uint32_t MAX_CAP = 5
    label_table->symbol_count = 0; 
    label_table->max_cap = MAX_CAP;

    return label_table;
}

int add_label_to_table_61cAssembler(char* label_token, SymbolTable* label_table, uint32_t addr){
    
    // TODO check addr align should be multiple of 4

    // TODO check duplicated label names

    // expand linked list if full 
    if (label_table->symbol_count == label_table->max_cap)
    {
        Symbol *label_table->sym = realloc(sizeof(struct Symbol), max_cap + MAX_CAP);
        label_table->max_cap +=5;
    }
    // populates Symbol struct 
    label_table->sym[symbol_count]->label = malloc(sizeof(strlen(label_token))) // malloc saves uninitializable char* 
    strcpy(label_table->sym[symbol_count]->label, label_token); // .label vs ->label ??
    label_table->sym[symbol_count]->addr = addr;
    label_table->symbol_count += 1;

}

*************************************************************************************************/




/************************************************************************************************


*************************************************************************************************/
char** split(char* line){ 
  
  // null pointer points to the base address of segment
  // char** split_line = NULL; // array that stores the string    
  char* split_line[] = malloc(sizeof(char*)*num_element); // same as char** split_line but writable
  int num_element = 0;
  
  char* strtok_ptr = strtok(line, " "); // ' ' instead ??
  split_line[num_element] = strtok_ptr;

  while(strtok_ptr){    
    // char** split_line = realloc(split_line, sizeof(char*)* ++num_element);
    num_element ++;

    split_line = realloc(split_line, sizeof(char*)*num_element); // realloc(split_line, sizeof *strtok_ptr * num_element); // dereference is easier if datatype changes
    split_line[num_element] = strtok_ptr; // append ptr to string to array, strtok_ptr is word token string   
    
    strtok_ptr = strtok(NULL, " "); // advancing ptr to next whitespace
  }
  
  // why null-terminated string ??
  // split_line = realloc(split_line, sizeof(char*)* ++num_element);
  // split_line[num_element] = 0;
  
  // do i need to double free strtok_ptr as well ?? => yes but not free here
  
  return split_line;
}

/************************************************************************************************
*************************************************************************************************/

void first_pass_61cAssembler(char *filename){

  FILE *f = fopen(filename, "r");
  char line[1000];
  int c; // c is int since EOF is negative number and char is unsigned
  int n =0;

  while((c=getc(f))!= EOF){
    //putchar(c); // write char to stdout + faster than printf
    //if(c == '\n') printf("line break"); // if "n" there will be string literal use strcmp error
    line[n] = c;
    n++;
    if(c=='\n') {
      line[n+1] = '\0'; // null terminate string otherwise undefined behavior
      //printf("%s", line);      
      
      /* strtok_ptr points at the string tokens */       
      char* strtok_ptr = strtok(line, " "); //TODO
      while(strtok_ptr!=NULL){        
        printf("%s\n", strtok_ptr);        

        /* your code here */
        /*
        check if the label contains : at the end => if yes =>
        take that token and add to dict of label and addr
        
        addr_cntr + str[]
        */
        
        strtok_ptr = strtok(NULL, " ");
      }
      
      n = 0;
      memset(line, 0, sizeof(line)); // ** READ MEMSET zeor entire string up till null character, strlen(line)=>werid print 
      //strcpy(line,""); // empty string  
      //line[0] = '\0';     
    }
  }
}





