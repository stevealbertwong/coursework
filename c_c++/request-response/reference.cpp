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