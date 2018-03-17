/*
https://stackoverflow.com/questions/1433204/how-do-i-use-extern-to-share-variables-between-source-files


Best way to declare and define global variables:

Although there are other ways of doing it, the clean, reliable way to declare and define global variables is to use a header file file3.h to contain an extern declaration of the variable. The header is included by the one source file that defines the variable and by all the source files that reference the variable. For each program, one source file (and only one source file) defines the variable. Similarly, one header file (and only one header file) should declare the variable.



function: 
And as the extern extends the visibility to the whole program, the functions can be used (called) anywhere in any of the files of the whole program provided the declaration of the function is known. (By knowing the declaration of the function, C compiler knows that the definition of the function exists and it goes ahead to compile the program).

variable: 
f we put the presence of extern in variable as default then the memory for them will not be allocated ever, they will be declared only. Therefore, we put extern explicitly for C variables when we want to declare them without defining them. 

see: http://www.geeksforgeeks.org/understanding-extern-keyword-in-c/
*/
#include "file3.h"
#include "prog1.h" // functions declarations if file1.c, file2.c
#include <stdio.h>

int main(void)
{
  use_it();
  global_variable += 19;
  use_it();
  printf("Increment: %d\n", increment());
  return 0;
}
