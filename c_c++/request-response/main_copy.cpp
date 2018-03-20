/*

g++ -std=c++11 -o main main.cpp
*/
#include <iostream>
#include <stdio.h>
#include <sys/types.h> // Data types used in socket.h and netinet/in.h
#include <sys/socket.h> // Struct definitions for sockets
#include <netinet/in.h> // Constants and structs for IP addresses
#include <stdlib.h>
#include <strings.h>
#include <sys/wait.h> // waitpid()
#include <signal.h> // Signal name macros and kill()
#include <string>
#include <unistd.h>
#include <unordered_map>
#include <iostream> // cout (for debugging)
#include <fstream> // ifstream
#include <sstream> // stringstream
#include <algorithm> // transform
#include <sys/stat.h> // stat for file time modification info

using namespace std;

int main(int argc, char const *argv[])
{

	// convert char* into string
	const char *s = "HTTP/1.1 200 OK\r\n Server: nginx/1.2.1\r\n Content-Type: text/html\r\n";
    // string request("HTTP/1.1 200 OK\r\n");
    string request(s);
    // request.append(request_message, *n);
    cout << "request_message in string: " << request.c_str() << endl;

    size_t start = 0;
    size_t end = 0;

    string method;
    string uri;
    string version;

    // Get method, URI, and version info
    end = request.find(' ', start);
    if (end == string::npos)
        return 0;
    method = request.substr(start, end - start);
    start = end + 1;
    end = request.find(' ', start);
    if (end == string::npos)
        return 0;
    uri = request.substr(start, end - start);
    start = end + 1;
    end = request.find("\r\n", start);
    if (end == string::npos)
        return 0;
    version = request.substr(start, end - start);
    start = end + 2;

    cout << "Method: " << method << endl;
    cout << "URI: " << uri << endl;
    cout << "Version: " << version << endl;
    
    unordered_map<string, string> headers;
    // Store headers into the map declared above
    while (true)
    {
        string key, value;

        end = request.find(": ", start);
        if (end == string::npos)
            break;
        key = request.substr(start, end - start);
        start = end + 2;
        end = request.find("\r\n", start);
        if (end == string::npos)
            break;
        value = request.substr(start, end - start);
        start = end + 2;

        cout << "Key: " << key << " Value: " << value << endl;
        headers[key] = value;

    }
	// Iterate over an unordered_map using range based for loop
	for (pair<std::string, std::string> element : headers)
	{
		std::cout << element.first << " : " << element.second << std::endl;
	}
		
	return 0;
}