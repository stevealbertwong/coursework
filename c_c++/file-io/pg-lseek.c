/*
30 Jan 2017
http://codewiki.wikidot.com/c:system-calls:lseek

http://stackoverflow.com/questions/10353243/linux-programming-value-of-file-descriptor-is-always-3

https://www.safaribooksonline.com/library/view/linux-system-programming/0596009585/ch02s07.html

gcc -Wall lseek-test.c -o lseek-test

offset -> starting position to read a file

*/

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>

#define BLOCKSIZE 512
#define CACHE_OFFSET(O)   (O & (BLOCKSIZE - 1))

int main(int argc, char const *argv[])
{
	

	int fd = STDIN_FILENO; // 0
	// printf("%d\n", fd);
	fd = open("lseek-test.txt", O_RDONLY);
	// printf("%lu\n", sizeof(fd)); // lu unsigned long + sizeof -> size of datatype i.e. int = 4 does not matter how big the file is
	// printf("%d\n", fd); // file desciptor always 3 -> Processes start with pre-opened file descriptors: 0 for stdin, 1 for stdout and 2 for stderr. Any new files you open should start with 3. If you close a file, that file descriptor number will be re-used for any new files you open
	// int fd2 = open("lseek-test.txt", O_RDONLY);
	// printf("%d\n", fd2); // print 4
	
	char buffer1[50];
    read(fd,buffer1,40);// read first 10 bytes of file into buffer array -> return no of bytes read
    printf("buffer1 : %s\n",buffer1);


    char buffer2[50];
	lseek(fd,20,SEEK_SET); // SEEK_SET offset measured in absolute terms
	lseek(fd,10,SEEK_CUR); // relative to current location of pointer, adjust existing offset pointer
	// lseek(fd,10,SEEK_END); // relative to end of file
	read(fd,buffer2,60);
	printf("buffer2 : %s\n",buffer2);

	return 0;
}


