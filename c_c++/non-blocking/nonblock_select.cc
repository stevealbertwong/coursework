/*
** select.c -- a select() demo
http://beej.us/net2/bgnet.html#advanced

you have 2.5 seconds to press key, otherwise time out

g++ -std=c++14 nonblock_select.cc -o nonblock_select
*/

#include <stdio.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#define STDIN 0  // file descriptor for standard input
int main(void)
{
    struct timeval tv; // set timeout
    fd_set readfds;
    tv.tv_sec = 2;
    tv.tv_usec = 500000;
    FD_ZERO(&readfds); // clear fd sets
    FD_SET(STDIN, &readfds); // add STDIN to readfd sets
    // select() => readfds contain fd that received stuff
    // writefd, exceptfd: NULL
    select(STDIN+1, &readfds, NULL, NULL, &tv); 
    // FD_ISSET() => test which fd received stuff
    if (FD_ISSET(STDIN, &readfds))
        printf("A key was pressed!\n");
    else
        printf("Timed out.\n");

    return 0;
} 