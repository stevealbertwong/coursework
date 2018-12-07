#include <stdio.h>
#include <stdlib.h>
#include "tests.h"

int main(){
  int x;
  // x = test_bitAnd(1, 3);
  x = test_tmin();
  printf("%x\n", x);


  int min = (~0) << 31; // int is 4 bytes, 32 bits
  int max = ~((~0) << 31);
  printf("%x\n", min);  
  printf("%d\n", min); // INT RANGE: 2^31-1 (MAX) -2^31 (MIN) 
  printf("%x\n", max);
  printf("%d\n", max);

  long z = (~0L) << 63; // long is 8 bytes, 64 bits
  printf("%ld\n", z);
  printf("%lx\n", z);

  // int a = 0xF00; // 15 * 16^2
  int c = 0xBE; // 11 * 16 + 14

  char * b = "0x7F800001";
  printf("%s\n", b);
  printf("%d\n", c);

  int d = -1000000;
  int e = d >> 4; // arithmetic shift replicate 1 on the leftmost
  printf("%x\n", d);
  printf("%x\n", e);

  unsigned int un_int = (~0); // unsigned int max => 4294967295
  printf("%u\n", un_int);

  // itoa does not work with c99
  // int itoa_ = 10;
  // char buffer [33];
  // itoa (itoa_, buffer, 2);
  // printf("%s\n", buffer);

  // printing binary in reverse
  // int n = 10; 
  // while (n) {
  //   if (n & 1)
  //       printf("1");
  //   else
  //       printf("0");
  //   n >>= 1;
  //   }

  char str[] = "abc";
  printf("%c\n", str[3]); // 3 is null terminated character => by convention indicating the end of string

  char *a = "stpud\0hey\0\0";
  printf("%s\n", a);

  x = bitMask(5,3);
  printf("%d\n", x);


  return 0;

}
