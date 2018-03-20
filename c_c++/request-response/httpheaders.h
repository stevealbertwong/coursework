#ifndef _HTTP_HEADERS_H_
#define _HTTP_HEADERS_H_

#include <unordered_map>
#include <string>
#include <stdio.h> // size_t
#include <iostream>

using namespace std;

class HttpHeaders{
public:
  HttpHeaders();
  void ParseHeaders(string& request);
  // size_t GetTotalHeaders();

  // FindHeaders();
  // AddHeaders();
  // RemoveHeaders();
  // ModifyHeaders();

  // EngineerHeaders();

  // unordered_map<string, string> GetHeaders();
  size_t getStart() const {return start;}
  size_t getEnd() const {return end;}

  // const std::string& getMethod() const { return method; }

// inherited subclass could access
protected:
  size_t start = 0;
  size_t end = 0;

// only httpheader class could access
private:
  unordered_map<string, string> headers;

};


#endif // _HTTP_HEADERS_H_