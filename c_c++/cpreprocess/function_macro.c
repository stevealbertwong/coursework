/*
Collection of beautiful function macros

malloc lab
http://www.cplusplus.com/doc/tutorial/preprocessor/
*/

#include <stdio.h>

#define MAX(x,y) ((x)>(y)?(x):(y))

int main(){
    int compare = MAX(1,2);
    printf("%d",compare);

    return 0;
}