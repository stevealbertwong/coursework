/*
no error checking for clean logic
author: steven wong

g++ -std=c++14 test_select.cc -o test_select

// telnet establish tcp session
telnet localhost 8888 
telnet 127.0.0.1 8888
then type hello, hello will show up in every connected terminal
*/
#include <stdio.h>
#include <string.h>   //strlen
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>   //close
#include <arpa/inet.h>    //close
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/time.h> //FD_SET, FD_ISSET, FD_ZERO macros
#include <iostream>
#define TRUE   1
#define FALSE  0
#define PORT 8888
#define MAXCLIENTS 30
// using namespace std;

sockaddr_in fill_serveraddr(){
	struct sockaddr_in address; 
	address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons( PORT );
	return address;
}

// void send_all_connected_clients(){
//     for(j = 0; j <= max_fd; j++) {        
//         if (FD_ISSET(j, &masterfd)) {
//             // except the server and the guy that sent
//             if (j != server_socket && j != i) {
//                 send(j, buffer, sizeof(buffer), 0);                
// }

int main(int argc, char const *argv[])
{
	int opt = TRUE; // setsockopt()
	int addrlen, num_active_sockets, i , valread , sd, max_fd;
	int rf; // function's return flag
	int server_socket; // server socket()
	int client_socket; // accept() => client fds	
	char buffer[1024];  // data buffer of 1K
	fd_set readfds; // set of client fds/connections in current select()
	fd_set masterfd;   // set of all clients and server fds/sockets
	struct sockaddr_in serveraddr;     // server address
    struct sockaddr_in clientaddr; // client address
    
	server_socket = socket(AF_INET , SOCK_STREAM , 0);
	setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR, (char *)&opt, sizeof(opt));
    serveraddr = fill_serveraddr();
    ::bind(server_socket, (struct sockaddr *)&serveraddr, sizeof(serveraddr)); // socket bind to unique port
    listen(server_socket, 3); // 3 backlog == pending connections allowed incoming queue

    FD_ZERO(&masterfd);    // clear the master and working sets
    FD_ZERO(&readfds);
    FD_SET(server_socket, &masterfd); // 1 server socket in master set

    max_fd = server_socket; // as only 1 server socket, it is max, later update w client sock    
    while(1){    	
    	
        memcpy(&readfds, &masterfd, sizeof(masterfd)); // copy master set into working set
    	// readfds = masterfd; // same as above
    	
        num_active_sockets = select(max_fd + 1 , &readfds , NULL , NULL , NULL); // among all sockets(max_fd+1) if in readfds, update readfds
    	    	
    	for (i=0; i <= max_fd  &&  num_active_sockets > 0; ++i){ // if socket is active    		
    		
            if (FD_ISSET(i, &readfds)){ // for that active socket    			
    			num_active_sockets--;

    			if(i == server_socket){ // if its server socket => new client connections    				
    				client_socket = accept(server_socket, NULL, NULL); // accept is blocking + spawning new client_fds
    				std::cout << "new connections " << client_socket << std::endl;
    				FD_SET(client_socket, &masterfd); // add new clients to master set
    				if (client_socket > max_fd) max_fd = client_socket; // update max socket id    				    				
    			}
    			else{ // if existing connection => multiple new transfers
    				
					rf = recv(i, buffer, sizeof(buffer), 0); // rf == byte received, recv() is blocking					
					
                    // if(rf == 0){
					// 	getpeername(i , (struct sockaddr*)&clientaddr , sizeof(clientaddr));
					// 	printf("Host disconnected , ip %s , port %d \n" , inet_ntoa(clientaddr.sin_addr) , ntohs(clientaddr.sin_port));
					// }
					// send(i, buffer, sizeof(buffer), 0); // send back to sender
					
					buffer[rf] = '\0'; // clean garbage
					// send all peers
					for(int j = 0; j <= max_fd; j++) {        
				        if (FD_ISSET(j, &masterfd)) {
				            // except the server and the guy that sent
				            if (j != server_socket && j != i) {
				                send(j, buffer, rf+1, 0); }}}      		
    			}
    		}
    	}
    }


	return 0;
}