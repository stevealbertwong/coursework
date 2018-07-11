/*
https://stackoverflow.com/questions/13129340/recursive-function-for-listing-all-files-in-sub-directories

*/

#include <iostream>
#include <dirent.h>
#include <cstring>

using namespace std;

int main() {
   DIR* dir; dirent* pdir;
   //From my workspace
   dir=opendir(".");     
   while (pdir=readdir(dir)) {
       if(/**********This pdir is a directory**********/) {
           /**********RECURSIVE CALL SHOULD BE HERE**********/
           cout<<pdir->d_name<<endl;
       }
   }
   closedir(dir);
   return 0;
}