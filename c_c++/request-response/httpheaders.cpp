/*
class with header parsing methods and unordered_map of headers

*/
#include "httpheaders.h"

using namespace std;

// but if call in subclass here, add HttpHeader:: as scope if same name scope
HttpHeaders::HttpHeaders(){}

void HttpHeaders::ParseHeaders(string& request){    
  // start: starting position of request/response to find()
  while (true)
  {
      string key, value;
      start = getStart();
      end = getEnd();

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
}
