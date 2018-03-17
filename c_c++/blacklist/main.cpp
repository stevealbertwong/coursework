/*

fixing bug for cs110 multiprocess proxy


-std=c++0x => regex weird warning
g++ -g -Wall -std=c++0x -o main main.cpp blacklist.cpp
*/
#include <iostream>
#include <fstream>
#include <string>
#include <unistd.h> // getcwd
#include "blacklist.h"

using namespace std;
int main(int argc, char const *argv[])
{
	// char cCurrentPath[FILENAME_MAX];
 //    getcwd(cCurrentPath, sizeof(cCurrentPath));
 //    cCurrentPath[sizeof(cCurrentPath) - 1] = '\0';
 //    string blacklistFile = cCurrentPath + "/blocked-domains.txt"
    
 //    HTTPBlacklist blacklist("/home/steve/Desktop/proxy/blocked-domains.txt");
 //    cout << "blacklist initialized" << request_message << endl;
    
 //    if(blacklist.is_blacklisted(request_message)){
 //        cout << "blacklisted server: " << request_message << endl;
 //        exit(0);
 //    }
	string homeDomain("/home/steve/Desktop/proxy/blocked-domains.txt");
	cout << homeDomain.size() <<endl; // 45

	// ifstream infile("blocked-domains.txt");
	// string line;
	// getline(infile, line);
	// cout << line << endl;
	string filename("blocked-domains.txt");

	HTTPBlacklist blacklist(filename);

	return 0;
}