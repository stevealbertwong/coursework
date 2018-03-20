/*
c++ -std=c++11 -o test test.cpp
*/
#include <iostream>
#include <string>
#include <stdlib.h>
#include <fstream>
#include <sstream>
#include <dirent.h>
// #include <boost/filesystem.hpp> // not installed yet
#include <unistd.h>


// // get cwd
// #ifdef _WIN32
//     #include <direct.h>
//     #define getcwd _getcwd // stupid MSFT "deprecation" warning
// #elif
//     #include <unistd.h>
// #endif


// using boost::filesystem;
using namespace std;

int main(int argc, char const *argv[])
{
	// string homeDirectoryEnv = getenv("HOME");
	// cout << homeDirectoryEnv << endl;


	// string fullCacheEntryName = "/Users/SteveAndrewWong/Desktop/Stanford-class/COURSEWORK/c_c++/request-response/hihi";
	// ifstream instream(fullCacheEntryName.c_str(), ios::in | ios::binary);
	// string responseCodeLine;
 //  	getline(instream, responseCodeLine);
 //  	cout << responseCodeLine << endl;


  	static const size_t kMaxPath = 1024;
  	// look for hihi file in directory
  	const char *directory = "/Users/SteveAndrewWong/Desktop/Stanford-class/COURSEWORK/c_c++/request-response/.";
  	size_t length = strlen(directory);
  	char path[kMaxPath + 1];
  	strcpy(path, directory); // maybe buffer overflow: directory longer than path
  	DIR *dir = opendir(path);

	struct dirent *de = NULL;
	// print all files
	// http://www.dreamincode.net/forums/topic/59943-accessing-directories-in-cc-part-i/
  	
  	// while((de = readdir(dir)) != NULL ){ // or != 0
  	// 	cout << de->d_name << endl;
  	// }

  	int return_code;
  	struct dirent entry;
  	struct dirent *result;
  	// thread safe version of looping through
  	for (return_code = readdir_r(dir, &entry, &result); 
        result != NULL && return_code == 0; 
        return_code = readdir_r(dir, &entry, &result)) {
    
    	string dirEntry = entry.d_name;
    	cout << dirEntry << endl;

    	// if (dirEntry != "." && dirEntry != "..") 
     	//  		remove(dirEntry.c_str()); // remove files
  	}

  	const char *r = "GET http://www.google.com:80/index.html/ HTTP/1.0\r\nContent-Length:80\r\nIf-Modified-Since: Sat, 29 Oct 1994 19:43:31 GMT\r\n\r\n";
	string request(r);
  	hash<string> hasher;
  	ostringstream oss;
  	size_t str_hash = hasher(request); // ??
  	oss << str_hash;
  	cout << "hashed request: " << oss.str() << endl;
  	

  	
  	// https://stackoverflow.com/questions/3935874/boostfilesystem-relative-path-and-current-directory
	// boost::filesystem::path full_path(boost::filesystem::current_path());
	// auto cwd = boost::filesystem::current_path();
	// auto cwd = std::filesystem::current_path(); // c++17
	// std::cout << "Current path is : " << cwd << std::endl;



	char buffer[1000];
	char *answer = getcwd(buffer, sizeof(buffer));
	cout << answer << endl;
	string s_cwd;
	s_cwd = string(answer);
	cout << s_cwd << endl;
	// if (answer)
	// {
	//     s_cwd = answer;
	// }




  	// cout << path << endl;
  	// strcpy(path + length, "/"); // add / at the end of path
  	// cout << path << endl;
  	// strcpy(path + length + 1, de->d_name);
  	// cout << path << endl;

	return 0;
}