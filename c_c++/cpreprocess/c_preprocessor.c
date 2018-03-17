/*
Practicing c prepocessor directives 
    => any lines starting with hashtag is prepocessor directives 
    => include + header
    => macro (#define, #undef)


# import module 
gcc c_preprocessor.c cpre_import.c -o c_preprocessor

# c preprocessor
gcc -E c_preprocessor.c > c_preprocessor.i

http://www.thegeekstuff.com/2012/10/gcc-compiler-options/?utm_source=feedburner

# assembly
gcc -S c_preprocessor.c > c_preprocessor.s

# compiled code without linking i.e. many .o

# all intermediate files i.e. .i .s .o
gcc -save-temps c_preprocessor.c
gcc -save-temps c_preprocessor.c cpre_import.c -o c_preprocessor


http://www.cplusplus.com/doc/tutorial/preprocessor/
*/

// #define myprint(str) prepossessed(str) 
#define prepossessed(str) myprint(str)

#include <stdio.h>
#include "cpre_import.h"

// void prepossessed(char *str){
//     printf("preposssessed %s\n", str);    
// }

/* dup function error */
// void myprint(char *str){
//     printf("myprint %s\n", str);    
// }

int main(){
    char name[] = "steven";
    myprint(name);
    prepossessed(name);
    return 0;
}