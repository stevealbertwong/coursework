/*
http://www.martinbroadhurst.com/list-the-files-in-a-directory-in-c.html
*/

#include <sys/types.h>
#include <dirent.h>
 
void read_directory(const std::string& name, stringvec& v)
{
    DIR* dirp = opendir(name.c_str());
    struct dirent * dp;
    while ((dp = readdir(dirp)) != NULL) {
        v.push_back(dp->d_name);
    }
    closedir(dirp);
}