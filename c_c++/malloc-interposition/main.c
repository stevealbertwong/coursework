/*
http://www.geeksforgeeks.org/function-interposition-in-c-with-an-example-of-user-defined-malloc/
*/

#include <stdio.h>
#include <stdlib.h>
// #include <malloc.h>
#include "malloc.h"
 
int main(void)
{
    // Call to user defined malloc => c prepocessor change malloc into mymalloc(4)
    void *ptr = malloc(4);
     
    printf("call from main, ptr addr %p\n", ptr);
    return 0;
}