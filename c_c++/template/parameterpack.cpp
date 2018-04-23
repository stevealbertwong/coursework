/*
http://en.cppreference.com/w/cpp/language/parameter_pack

g++ -std=c++11 parameterpack.cpp -o parameterpack
*/

#include <iostream>
 
void tprintf(const char* format) // base function
{
    std::cout << format;
}
 
template<typename T, typename... Targs>
void tprintf(const char* format, T value, Targs... Fargs) // recursive variadic function
{
    for ( ; *format != '\0'; format++ ) {
        if ( *format == '%' ) {
           std::cout << value;
           tprintf(format+1, Fargs...); // recursive call
           return;
        }
        std::cout << *format;
    }
}
 
int main()
{
    tprintf("% world% %\n","Hello",'!',123);
    return 0;
}



