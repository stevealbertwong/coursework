/*

g++ -std=c++11 -o main main.cpp

g++ -std=c++11 -o main main.cpp httprequest.cpp httpheaders.cpp httpresponse.cpp compat.cpp

g++ -std=c++11 -o main main.cpp httpheaders.cpp httpresponse.cpp cache.cpp

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
#include <dirent.h> // opendir(), readdir_r()

#include "httprequest.h"
#include "httpresponse.h"
#include "cache.h"


using namespace std;

int main(int argc, char const *argv[])
{

	// convert char* into string
	const char *s = "HTTP/1.1 200 OK\r\nServer: nginx/1.2.1\r\nContent-Type: text/html\r\n";

	string response(s);

	const char *r = "GET http://www.google.com:80/index.html/ HTTP/1.0\r\nContent-Length:80\r\nIf-Modified-Since: Sat, 29 Oct 1994 19:43:31 GMT\r\n\r\n";
	string request(r);


	// HttpResponse httpresponse;
	// httpresponse.ParseResponse(response);
	
	HttpCache httpcache;
	httpcache.saveCache(request, response);

	cout << httpcache.ensureEntryExists(request) << endl;

	if(httpcache.ensureEntryExists(request)){
		string re_response = httpcache.retrieveCache(request);
		cout << re_response << endl;
	}
	
	


	// string version;
	// string status;
	// string status_line;
	// size_t start = 0;
 //    size_t end = 0;

 //    std::unordered_map<std::string, std::string> headers;

 //    // parse response line: Get method, URI, and version info
 //    end = response.find(' ', start);
 //    if (end == string::npos)
 //        return 0;
 //    version = response.substr(start, end - start);
 //    start = end + 1;
 //    end = response.find(' ', start);
 //    if (end == string::npos)
 //        return 0;
 //    status = response.substr(start, end - start);
 //    start = end + 1;
 //    end = response.find("\r\n", start);
 //    if (end == string::npos)
 //        return 0;
 //    status_line = response.substr(start, end - start);
 //    start = end + 2;

 //    cout << "Http version: " << version << endl;
 //    cout << "status: " << status << endl;
 //    cout << "status_line: " << status_line << endl;


 //    // parse headers
 //    while (true)
 //    {
 //        string key, value;

 //        end = request.find(": ", start);
 //        if (end == string::npos)
 //            break;
 //        key = request.substr(start, end - start);
 //        start = end + 2;
 //        end = request.find("\r\n", start);
 //        if (end == string::npos)
 //            break;
 //        value = request.substr(start, end - start);
 //        start = end + 2;

 //        cout << "Key: " << key << " Value: " << value << endl;
 //        headers[key] = value;

 //    }
 //    // Iterate over an unordered_map using range based for loop
 //    for (pair<std::string, std::string> element : headers)
 //    {
 //        std::cout << element.first << " : " << element.second << std::endl;
 //    }

    // string request("HTTP/1.1 200 OK\r\n");
    // string request_string(s);    
    // // cout << s.length() << endl;
    // // // request.append(request_message, *n);
    // // cout << "request_message in string: " << request_string.c_str() << endl;

    // HttpRequest request;
    // request.ParseRequest(request_string.c_str(), request_string.length());



    // const char * = "HTTP/1.1 200 OK\r\n Server: nginx/1.2.1\r\n Content-Type: text/html\r\n";

    
    // // string request("HTTP/1.1 200 OK\r\n");
    // string response_string(r);  


		
	return 0;
}