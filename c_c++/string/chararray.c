/*
2017-5-9
reviewing how to declare array
array of string
see: https://www.cs.bu.edu/teaching/cpp/string/array-vs-ptr/

single quote error
SINGLE QUOTE FUCKS ME UP WTF!!!!!!!!!!!!!
see: http://stackoverflow.com/questions/7459939/what-do-single-quotes-do-in-c-when-used-on-multiple-characters

why declaring variable out of the scope gives me error whereas declaring inside the scope just give me warning ??

*/
#include <stdio.h>

/* fuck single quote error ******************************************************** */
// SINGLE QUOTE FUCKS ME UP WTF!!!!!!!!!!!!!
// char wrd = {'steve', 'lemur'}; // size = 1 WTF
// char* wrd = {'steven', 'lemur'}; // size = 8 WTF, also it is only storing n (last char of 1st string)
// char wrd[] = {'steven', 'lemur'}; // size = 16, printing 1st element last 4 chars reversely
// char wrd[] = {"steven", "lemur"}; // size = 2 WTF

/********************************************************/




// char word[] = "steven"; // right way
// char word[100] = "steven"; // gives you more than you need



int main(int argc, char const *argv[])
{
	// word[0] = 'p';
	// printf("%c\n", word[0]);
	// word[1] = 't';
	// word[3] = 'p';
	// word[0] = 'p';

	/* string as array of char *********************************************************/
	
	// char* word[3] = "abc"; //ERROR => declaring an array that stores pointer instead of char
	char word[3] = "abc"; // right way but static allocation, size of array determined at compile time
	printf("word: %s\n", word);
	long long ptr_word1 = word;
	printf("ptr_word: %p\n", word);
	printf("ptr_word1: %p\n", ptr_word1);
	long long ptr_first_word = &word[0];
	long long ptr_sec_word = &word[1];
	long long ptr_four_word = &word[3]; // no seg fault
	long long ptr_six_word = &word[5]; // no seg fault => ptr arithmetic
	printf("ptr_first_word : %p\n", ptr_first_word);
	printf("ptr_sec_word : %p\n", ptr_sec_word);
	printf("ptr_four_word : %p\n", ptr_four_word);
	printf("ptr_six_word : %p\n", ptr_six_word);

	int num = 12;
	int num_arr[] = {99, 2719721, 2818812};
	int num_fake_arr = {99, 2719721, 2818812};
	long long num_arr_addr = &num_arr; // SUBSCRIBED VALUE NOT AN ARRAY, POINTER, VECTOR
	printf("num_arr : %p\n", num_arr);
	printf("num_arr_addr : %p\n", num_arr_addr); 
	printf("num_arr_addr2 : %p\n", &num_arr[1]);
	// printf("num_arr_addr : %p\n", num_arr_addr);
	printf("%d\n", num_arr[0]);
	printf("num_fake_arr: %d\n", num_fake_arr); // 1st element in array
	printf("num_fake_arr_addr: %p\n", &num_fake_arr); // 1st element in array
	int* num_arr_ptr = num_arr;
	printf("num_arr_ptr_value %p\n", num_arr_ptr);

	/********************************************************/


	/*array of strings *********************************************************/

	char *wrd[] = {	"steven", "lemur"}; // works => array of ptrs pointing at sting
	char ptr_wrd = wrd;
	int ptr_wrd_int = wrd; // should be long long
	char* ptr_wrd2 = wrd;
	char** ptr_wrd3 = wrd; // if same why need & => if var then & if already addre then no need
	char** ptr_wrd4 = &wrd;
	printf("wrd %p\n", wrd);
	printf("ptr_wrd_char %p\n", ptr_wrd);
	printf("ptr_wrd_int %p\n", ptr_wrd_int);
	printf("ptr_wrd2 %p\n", ptr_wrd2);
	printf("ptr_wrd3 %p\n", ptr_wrd3);
	printf("ptr_wrd4 %p\n", ptr_wrd4);
	
	char* str_arr[2];
	str_arr[0] = "steve"; 
	str_arr[1] = "lemur";
	printf("%s\n", str_arr[0]); 
	printf("pt1 %p\n", wrd); // same
	printf("pt2 %p\n", (void*)&wrd); // same, suggested typecasting, but no difference

		// printf("pt1 %04x %p\n", wrd, wrd); // same
		// printf("pt2 %04x\n", &wrd); // same

	printf("pt1 %04x %p\n", wrd[0], wrd[0]);
	printf("pt2 %p\n", wrd[1]);

	// char a[2][14];
	// strcpy(a[0], "blah");
	// strcpy(a[1], "hmm");
	// printf("%s\n", a[0]);

	/********************************************************/

	


	// int count = sizeof(word);
	// int count = sizeof(wrd); // ptr => 8 bytes
	int count = sizeof(wrd) / sizeof(char*); // SMART WAY TO GET THE REAL COUNT ********
	printf("%d\n", count);
	// printf("%s\n", wrd); // neve WTF 
	// printf("%s\n", wrd[0]); // neve WTF + segfault WTF

	for (int i = 0; i < count; ++i)
	{
		printf("%s\n", word); // seg fault if print string
		// printf("%s\n", wrd);
		printf("%s\n", wrd[i]);				
	}

	return 0;
}


