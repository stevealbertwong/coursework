/*
https://stackoverflow.com/questions/37538/how-do-i-determine-the-size-of-my-array-in-c
https://www.geeksforgeeks.org/how-to-find-size-of-array-in-cc-without-using-sizeof-operator/
https://stackoverflow.com/questions/16019009/find-size-of-array-without-using-sizeof-in-c
https://stackoverflow.com/questions/492384/how-to-find-the-sizeof-a-pointer-pointing-to-an-array

g++ -std=c++14 sizeof.cc -o sizeof

sizeof of array: 28
sizeof of parameter: 8
Length of array: 7
Length of parameter: 2

sizeof() iff arrays on stack. 
array uint8_t* arr / uint8_t arr[] sent as a parameter to a 
function is treated as a pointer, so sizeof will return the 
pointer's size, instead of the array's.

Note that this trick will only work in places where sizeof would have worked anyway
*/
#include <stdio.h>
#include <stdlib.h>

#include </Users/SteveAndrewWong/stdc++.h>
using namespace std;
 
// User defined sizeof macro => &type pointing at whole array instead of 1st element
# define my_sizeof(type) ((char *)(&type+1)-(char*)(&type))

void printSizeOf(int intArray[])
{
    printf("sizeof of parameter: %d\n", (int) sizeof(intArray));
}

void printLength(int intArray[])
{
    printf("Length of parameter: %d\n", (int)( sizeof(intArray) / sizeof(intArray[0]) ));
}

void macro_sizeof(int *arr){
   	// int  arr[] = {1, 2, 3, 4, 5, 6};
    
    int size = my_sizeof(arr)/my_sizeof(arr[0]);
 
    cout << "& pointing at whole array "
         << my_sizeof(arr) << endl;
    cout << "Number of elements in arr[] is "
         << size << endl;
}

void pointer_hack(int *arr){
	// int  arr[] = {1, 2, 3, 4, 5, 6};
    int size = *(&arr + 1) - arr;
    cout << "Number of elements in arr[] is "
         << size << endl;
}

void printSizeOf(int intArray[]);
void printLength(int intArray[]);

int main(int argc, char* argv[])
{
    int array[] = { 0, 1, 2, 3, 4, 5 };

    printf("sizeof of array: %d\n", (int) sizeof(array));
    printSizeOf(array);

    printf("Length of array: %d\n", (int)( sizeof(array) / sizeof(array[0]) ));
    printLength(array);
    macro_sizeof(array);
    pointer_hack(array);
}

