/*
#include <iostream>
#include <stdlib.h>
#include <string>

using namespace std;


int main(int argc, char const *argv[])
{
	string homeDirectoryEnv = getenv("HOME");

	cout << homeDirectoryEnv << endl;
	return 0;
}
*/

// https://stackoverflow.com/questions/143174/how-do-i-get-the-directory-that-a-program-is-running-from
#include <stdio.h>  /* defines FILENAME_MAX */
#ifdef WINDOWS
    #include <direct.h>
    #define GetCurrentDir _getcwd
#else
    #include <unistd.h>
    #define GetCurrentDir getcwd
#endif


int main(int argc, char const *argv[])
{
	 char cCurrentPath[FILENAME_MAX];

	 if (!GetCurrentDir(cCurrentPath, sizeof(cCurrentPath)))
	     {
	     
	     }

	cCurrentPath[sizeof(cCurrentPath) - 1] = '\0'; /* not really required */

	printf ("The current working directory is %s", cCurrentPath);
	return 0;
}

