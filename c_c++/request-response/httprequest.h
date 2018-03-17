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

    void parseRequestLine(std::istream& instream);
    void parseHeaders(std::istream& instream);


  private:
    std::string requestLine;
    // all request fields of dicts other than 1st line e.g. User-Agent: Mozilla/5.0
    
    // cleaned up n parsed version of 1st request line
    std::string method;
    std::string url;
    std::string server; 
    unsigned short port;
    std::string path;
    std::string protocol;

    std::unordered_map<std::string, std::string> headers;
    
};

#endif