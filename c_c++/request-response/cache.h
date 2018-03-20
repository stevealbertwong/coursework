#ifndef _CACHE_H_
#define _CACHE_H_

#include <sys/stat.h> // lstat()
#include <dirent.h> // opendir(), readdir_r()
#include <string>
 #include <stdio.h> // getline()

using namespace std;

class HttpCache{
public:
	HttpCache();
	// 1st const reference parameter: ensure orignal parameter passed wont get amended, if pass by value(copy) changed should not matter
	// 2nd const function: function wont change any class variable but ok local variable of function + cannot call non-const function even if such non-const function does not change class variable
	void ensureDirectoryExists(const string& directory, bool empty = false) const; 
	void ensureFileExists(const string& directory, bool empty = false) const; 

	void cacheEntry(string request, string response);


	bool checkCache(string request);
	string returnCache();
	


};

#endif