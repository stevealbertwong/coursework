#include "file3.h"  /* Declaration made available here */
#include "prog1.h"  /* Function declarations */

/* 
Variable defined here 
You may declare a variable multiple times (though once is sufficient); you may only define it once within a given scope.
*/

int global_variable = 37;    /* Definition checked against declaration */

int increment(void) { return global_variable++; }
