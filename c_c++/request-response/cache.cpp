#include <iostream>
#include "cache.h"

HttpCache::HttpCache(){
	// ensureDirectoryExists();
}

/* create dir to save cache */
//https://techoverflow.net/2013/04/05/how-to-use-mkdir-from-sysstat-h/
// static const int kDefaultPermissions = 644;
static const int kDefaultPermissions = 0777; // rwxrwxrwx 
void HttpCache::ensureDirectoryExists(const string& directory, bool empty) const {
  struct stat st;
  if (lstat(directory.c_str(), &st) != 0)
    mkdir(directory.c_str(), kDefaultPermissions);
  
  if (!empty) return;

  DIR *dir = opendir(directory.c_str());

  /* struct dirent
  file system independent directory entry/ format of directory entries
  Different file system types may have different directory entries 
  dirent structure defines a file system independent directory entry, 
  which contains information common to directory entries in different file system types
  */
  int return_code;
  struct dirent entry;
  struct dirent *result; 
  
  // loop through entries/file in directory
  for (return_code = readdir_r(dir, &entry, &result); 
        result != NULL && return_code == 0; 
        return_code = readdir_r(dir, &entry, &result)) {
    
    string dirEntry = entry.d_name;
    if (dirEntry != "." && dirEntry != "..") 
      remove(dirEntry.c_str());
  }
  
  closedir(dir);
}


/*
loop through directory to ensure such cache file exist
https://stackoverflow.com/questions/12774207/fastest-way-to-check-if-a-file-exist-using-standard-c-c11-c
*/
bool HTTPCache::cacheEntryExists(const string& requestHash) const {
  
  string path = cacheDirectory + "/" + requestHash;
    
  struct stat st;
  // lstat is improved version of stat that does symbolic links
  if (lstat(path.c_str(), &st) != 0) return false;
  if (!S_ISDIR(st.st_mode)) return false;

  int return_code;  
  struct dirent entry;
  struct dirent *result;
  
  
  DIR *dir = opendir(path.c_str());
  bool exists = false;
  /* Inspiration for this loop from IBM */
  for (return_code = readdir_r(dir, &entry, &result); 
        result != NULL && return_code == 0; 
        return_code = readdir_r(dir, &entry, &result)) {
    string dirEntry = entry.d_name;
    exists = dirEntry != "." && dirEntry != "..";
  }
  closedir(dir);
  return exists;
}








// TODO full directory path + hash 
void HttpCache::cacheEntry(string request, string response){
	// ios::out => opens file for writing
	// ios::binary => data is read or written without translating new line characters to and from \r\n on the fly
	// | => both => writing without translating
	string cacheEntryName = "hihi";
	ofstream outfile(cacheEntryName.c_str(), ios::out | ios::binary);
	outfile << response << flush;
}

// given request + hashed to get full directory path + return false if not exist
bool checkCache(const string request, string response) const {
	// check if fullCacheEntryName exist

	string requestHash = hashRequest(request);
	string fullCacheEntryName = cacheDirectory + "/" requestHash;



	ifstream instream(fullCacheEntryName.c_str(), ios::in | ios::binary);
	string responseCodeLine;
  	getline(instream, responseCodeLine);
  	cout << responseCodeLine << endl;

}







