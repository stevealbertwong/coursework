/*
https://stackoverflow.com/questions/34751873/how-to-read-huge-file-in-c
https://www.youtube.com/watch?v=DTxHyVn0ODg&t=914s

g++ -std=c++14 chararry_bigfile_heap.cc -o chararry_bigfile_heap
*/
#define TEST_DATA "test.data"
#define LOG(x) std::cout << x << std::endl;

#include <iostream>
#include <fstream>
#include <string>
#include <memory> // make_unique + unique_ptr

using namespace std;

void load(std::string filename){
	
	ifstream bigFile(filename);
	constexpr size_t bufferSize = 1024 * 1024;
	unique_ptr<char[]> buffer(new char[bufferSize]);
	// c++14, exception safe, if constructor throw exception, wont have dangling pointer
	// unique_ptr<char[]> buffer = std::make_unique<char[]>(bufferSize);

	while (bigFile)
	{	
		// unique_ptr.get() returns a pointer to managed object
	    bigFile.read(buffer.get(), bufferSize);	    
	}

	// LOG(((void *)buffer));	
	// LOG(static_cast<void *>(buffer));
	std::cout << buffer.get() << std::endl;
}


int main(int argc, char const *argv[])
{
	load(TEST_DATA);
	return 0;
}