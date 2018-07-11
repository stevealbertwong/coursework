/*
http://www.cplusplus.com/forum/beginner/40783/
*/
#include <iostream>
using namespace std;

int main(){

        int arr1[]= {1, 2, 3, 4, 5};
        char * str1 = "This is a test for sizeof()";
        char str2[] = "This is a test for sizeof()";
        char str3[] = { 'C', '+' , '+' };

        cout << "Sizeof arr1 " << sizeof(arr1) << endl;
        cout << "Sizeof str1 " << sizeof(str1) << endl;
        cout << "Sizeof str2 " << sizeof(str2) << endl;
        cout << "Sizeof str3 " << sizeof(str3) << endl;

        cout << "Length of arr1 by formula " <<  sizeof(arr1) / sizeof(*arr1) << endl;
        cout << "Length of str1 by formula " <<  sizeof(str1) / sizeof(*str1) << endl;
        cout << "Length of str2 by formula " <<  sizeof(str2) / sizeof(*str2) << endl;
        cout << "Length of str3 by formula " <<  sizeof(str3) / sizeof(*str3) << endl;