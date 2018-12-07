
#include <stdio.h>
#include <math.h>
#include <stdlib.h>


/*
http://cs-fundamentals.com/c-programming/structure-alignment-and-padding-in-c.php

1. biggest data type -> becomes alignment
2. optimize order according to alignment/biggest data type 
3. safe -> big data type to small

*/

void test_alignment(){
	// declare members in random order
  typedef struct
  {
   char ch1; short sh1;
   char ch2; float fl1;
   int in1; char ch3;
   double dbl1;
  } random_struct;
 
  // declare members from largest to smallest order
  typedef struct
  {
   double dbl1; float fl1;
   int in1; short sh1;
   char ch1, ch2, ch3;
  } ordered_struct;

  typedef struct{
  	
  	// int in1;
  	
  	// char ch1, ch2, ch3;
  	
  	double dd, dd2;
  	char ch1;
  	// double dd;
  	// int in2;
  	// short sh1, sh2, sh3, sh4, sh5;
  	// short sh1;
  	
  }optimized_struct;
 
 
  random_struct s1;
  ordered_struct s2;
  printf("Size of s1: %lu\n", sizeof(s1));
  printf("Size of s2: %lu\n", sizeof(s2));

  optimized_struct s3;
  printf("Size of s3: %lu\n", sizeof(s3));

}

int main(int argc, char const *argv[])
{
	test_alignment();
	return 0;
}