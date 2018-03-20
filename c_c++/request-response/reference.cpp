/**
 * We need to figure out what file we're after. Here's an easy way.
 * When we parse the HTTP header, we only care about the first line.

ucla 2013 fork server.cpp
 */
std::string Server::extract_requested_file( std::string request_data ) {
    char* request_copy = new char[request_data.size() + 1];
    memset( request_copy, '\0', request_data.size() + 1 );
    strncpy( request_copy, request_data.c_str(), request_data.size() );

    // Token now holds the method like GET or POST
    char *token = strtok( request_copy, " " );

    // Now we have the url
    token = strtok( NULL, " " );

    std::string file_name = "";

    if ( NULL != token )
        file_name = token;

    delete request_copy;

    // Bind the url root to index.html or remove the slash before the path
    if ( "/" == file_name )
        file_name = "index.html";
    else if( file_name[0] == '/' )
        file_name = file_name.substr(1, std::string::npos);

    return file_name;
}


/*
cs118 caching server, boost + sqlite
*/

const char*
HttpRequest::ParseRequest (const char *buffer, size_t size)
{
  const char *curPos = buffer;
  
  const char *endline = (const char *)memmem (curPos, size - (curPos-buffer), "\r\n", 2);
  if (endline == 0)
    {
      throw ParseException ("HTTP Request doesn't end with \\r\\n");
    }

  boost::char_separator<char> sep(" ");
  string requestLine (curPos, endline-curPos);
  boost::tokenizer< boost::char_separator<char> > tokens (requestLine,
                                                          boost::char_separator<char> (" "));
  
  // 1. Request type
  boost::tokenizer< boost::char_separator<char> >::iterator token = tokens.begin ();
  if (token == tokens.end ())
    throw ParseException ("Incorrectly formatted request");

  // TRACE ("Token1: " << *token);
  if (*token != "GET")
    {
      throw ParseException ("Request is not GET");
    }
  SetMethod (GET);

  // 2. Request path
  ++ token;
  if (token == tokens.end ())
    throw ParseException ("Incorrectly formatted request");

  // TRACE ("Token2: " << *token);
  size_t pos = token->find ("://");
  if (pos == string::npos)
    {
      // just path
      SetPath (*token);
    }
  else
    {
      // combined Host and Path
      string protocol = token->substr (0, pos);
      // TRACE (protocol);
      
      pos += 3;
      size_t posSlash = token->find ("/", pos);
      if (posSlash == string::npos)
        throw ParseException ("Request line is not correctly formatted");

      // TRACE (string (curPos, endline-curPos));
      // TRACE (*token);
      // TRACE (pos << ", " << posSlash);
      
      size_t posPort = token->find (":", pos);
      if (posPort != string::npos && posPort < posSlash) // port is specified
        {
          string port = token->substr (posPort + 1, posSlash - posPort - 1);
          // TRACE (port);
          SetPort (boost::lexical_cast<unsigned short> (port));

          string host = token->substr (pos, posPort-pos);
          // TRACE (host);
          SetHost (host);
        }
      else
        {
          SetPort (80);
          
          string host = token->substr (pos, posSlash-pos);
          // TRACE (host);
          SetHost (host);
        }

      string path = token->substr (posSlash, token->size () - posSlash);
      // TRACE (path);
      SetPath (path);
    }

  // 3. Request version
  ++token;
  if (token == tokens.end ())
    throw ParseException ("Incorrectly formatted request");
  // TRACE ("Token3: " << *token);
  size_t posHTTP = token->find ("HTTP/");
  if (posHTTP == string::npos)
    {
      throw ParseException ("Incorrectly formatted HTTP request");
    }
  string version = token->substr (5, token->size () - 5);
  // TRACE (version);
  SetVersion (version);
  
  curPos = endline + 2;
  return ParseHeaders (curPos, size - (curPos-buffer));
}




/*
very clean version

*/
#ifndef _http_request_h_
#define _http_request_h_

#include <iostream>
#include <string>
#include <vector>
#include <map>


class HTTPRequest {

  public:

    const std::string& getMethod() const { return method; }
    const std::string& getURL() const { return url; }
    const std::string& getServer() const { return server; }
    unsigned short getPort() const { return port; }
    const std::string& getPath() const { return path; }
    const std::string& getProtocol() const { return protocol; }

    void parseRequestLine(string request_string);
    


  private:
    std::string requestLine;
    // all request fields of dicts other than 1st line e.g. User-Agent: Mozilla/5.0
    
    // cleaned up n parsed version of 1st request line
    std::string method;
    std::string url;
    std::string version; 
    
    std::string server; 
    unsigned short port;
    std::string path;
    std::string protocol;

    std::unordered_map<std::string, std::string> headers;
    
};

#endif

#include "httprequest.h"

void HTTPRequest::parseRequestLine(string& request){
    size_t start = 0;
    size_t end = 0;

    // parse request line: Get method, URI, and version info
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

    
    // parse headers
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
}


/*

https://stackoverflow.com/questions/25896916/parse-http-headers-in-c
*/
void HTTPRequest::parseResponse(string& response){
    size_t start = 0;
    size_t end = 0;

    // parse response line: Get method, URI, and version info
    end = response.find(' ', start);
    if (end == string::npos)
        return 0;
    version = response.substr(start, end - start);
    start = end + 1;
    end = response.find(' ', start);
    if (end == string::npos)
        return 0;
    status = response.substr(start, end - start);
    start = end + 1;
    end = response.find("\r\n", start);
    if (end == string::npos)
        return 0;
    status_line = response.substr(start, end - start);
    start = end + 2;

    cout << "Http version: " << version << endl;
    cout << "status: " << status << endl;
    cout << "status_line: " << status_line << endl;

    
    // parse headers
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
}

