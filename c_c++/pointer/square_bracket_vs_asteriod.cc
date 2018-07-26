/*
https://www.geeksforgeeks.org/whats-difference-between-array-and-array-for-int-array5/

array” is a “pointer to the first element of array” but “&array” is a “pointer to whole array of 5 int”.


*/


#include "stdio.h"
int main()
{
   int array[5];
 
   /* If %p is new to you, you can use %d as well */
   printf("array=%p : &array=%p\n", array, &array); 
 
   printf("array+1 = %p : &array + 1 = %p", array+1, &array+1);
 
   return 0;
}