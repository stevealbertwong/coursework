/*
c++ -o test test.cpp
*/
#include <iostream>
#include <string>
#include <stdlib.h>
#include <fstream>
#include <dirent.h>

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
  	
  	
  	
  	// cout << path << endl;
  	// strcpy(path + length, "/"); // add / at the end of path
  	// cout << path << endl;
  	// strcpy(path + length + 1, de->d_name);
  	// cout << path << endl;

	return 0;
}