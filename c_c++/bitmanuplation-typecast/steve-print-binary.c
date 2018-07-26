/*
http://stackoverflow.com/questions/111928/is-there-a-printf-converter-to-print-in-binary-format?noredirect=1&lq=1
http://stackoverflow.com/questions/6373093/how-to-print-binary-number-via-printf

http://softwareengineering.stackexchange.com/questions/181505/what-is-a-null-terminated-string
*/
#include <stdio.h>      /* printf */
#include <string.h>     /* strcat */
#include <stdlib.h>     /* strtol */

const char *byte_to_binary(int x)
{
    static char b[9];
    b[0] = '\0'; // null terminating character => It's common practice to pre-fill and clear a string with nulls to get rid of any garbage.
    memset(b, 0x00, 9); // clear a string with nulls

    int z;
    for (z = 128; z > 0; z >>= 1) // 1000 0000 => 0100 0000 => 0010 0000 etc
    {
        strcat(b, ((x & z) == z) ? "1" : "0"); // concatenate source string to b
    }

    return b;
}

int main(void)
{
    {
        /* binary string to int */

        char *tmp;
        char *b = "0101";

        printf("%ld\n", strtol(b, &tmp, 2));
    }

    {
        /* byte to binary string */

        printf("%s\n", byte_to_binary(10));
    }

    return 0;
}