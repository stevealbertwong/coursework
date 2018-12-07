/*
http://beej.us/net2/bgnet.html#advanced

** selectserver.c -- a cheezy multiperson chat server

This program acts like a simple multi-user chat server. Start it running in one window, 
then telnet to it ("telnet hostname 9034") from multiple other windows. 
When you type something in one telnet session, it should appear in all the others.

master, holds all the socket descriptors that are currently connected, as well as the 
socket descriptor that is listening for new connections.
select() actually changes the set you pass into it to reflect which sockets are ready to read. 
keep track of the connections from one call of select() to the next, I must store these safely away somewhere

select() blocks a period of time and store fd that received electric wave

g++ -std=c++14 select_multi_chat_beej.cc -o select_multi_chat_beej

// telnet establish tcp session
telnet localhost 9034 
telnet 127.0.0.1 9034
then type hello, hello will show up in every connected terminal
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 9034   // port we're listening on

int main(void)
{
    fd_set master;   // master file descriptor list
    fd_set read_fds; // temp file descriptor list for select()
    struct sockaddr_in myaddr;     // server address
    struct sockaddr_in remoteaddr; // client address
    int fdmax;        // maximum file descriptor number
    int listener;     // listening socket descriptor
    int newfd;        // newly accept()ed socket descriptor
    char buf[256];    // buffer for client data
    int nbytes;
    int yes=1;        // for setsockopt() SO_REUSEADDR, below
    socklen_t addrlen;
    int i, j;
    char message[] = "ECHO Daemon v1.0 \r\n";

    FD_ZERO(&master);    // clear the master and temp sets
    FD_ZERO(&read_fds);

    // get the listener
    if ((listener = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("socket");
        exit(1);
    }

    // lose the pesky "address already in use" error message
    // allows mulitple connections
    if (setsockopt(listener, SOL_SOCKET, SO_REUSEADDR, &yes,
                                                        sizeof(int)) == -1) {
        perror("setsockopt");
        exit(1);
    }

    // bind() give unique port to socket
    myaddr.sin_family = AF_INET;
    myaddr.sin_addr.s_addr = INADDR_ANY;
    myaddr.sin_port = htons(PORT);
    memset(&(myaddr.sin_zero), '\0', 8);
    if (bind(listener, (struct sockaddr *)&myaddr, sizeof(myaddr)) == -1) {
        perror("bind");
        exit(1);
    }

    // listen on listenerfd, 10 backlog == pending connections allowed incoming queue
    if (listen(listener, 10) == -1) {
        perror("listen");
        exit(1);
    }

    // add the listener fd's 10 connections to the master set
    FD_SET(listener, &master);

    // keep track of the biggest file descriptor => equal to number of connections
    fdmax = listener; // so far, it's this one

    // main loop
    for(;;) {
        read_fds = master; // copy master into the read_fds, and then call select().
        // wait for an activity on one of the sockets , timeout is NULL , so wait indefinitely
        if (select(fdmax+1, &read_fds, NULL, NULL, NULL) == -1) {
            perror("select");
            exit(1);
        }

        // run through the existing connections looking for data to read
        // check all fds, which one in the set/got electric wave
        for(i = 0; i <= fdmax; i++) {

            // if any handshake/data
            if (FD_ISSET(i, &read_fds)) { 
                
                if (i == listener) {
                    // handle new connections
                    addrlen = sizeof(remoteaddr);
                    if ((newfd = accept(listener, (struct sockaddr *)&remoteaddr,
                                                             &addrlen)) == -1) { 
                        perror("accept");
                    } else {
                        FD_SET(newfd, &master); // add to master set
                        if (newfd > fdmax) {    // keep track of the maximum
                            fdmax = newfd;
                        }
                        printf("selectserver: new connection from %s on "
                            "socket %d\n", inet_ntoa(remoteaddr.sin_addr), newfd);
                    }
                } else {
                    // handle data from a client
                    if ((nbytes = recv(i, buf, sizeof(buf), 0)) <= 0) {
                        // got error or connection closed by client
                        if (nbytes == 0) {
                            // connection closed
                            printf("selectserver: socket %d hung up\n", i);
                        } else {
                            perror("recv");
                        }
                        close(i); // bye!
                        FD_CLR(i, &master); // remove from master set
                    } else {
                        // we got some data from a client
                        for(j = 0; j <= fdmax; j++) {
                            // send to everyone!
                            if (FD_ISSET(j, &master)) {
                                // except the listener and ourselves
                                if (j != listener && j != i) {
                                    if (send(j, buf, nbytes, 0) == -1) {
                                        perror("send");
                                    }
                                }
                            }
                        }
                    }
                } // it's SO UGLY!
            }
        }
    }
    
    return 0;
} 