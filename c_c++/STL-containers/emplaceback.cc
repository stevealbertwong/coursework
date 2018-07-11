//Compiled with G++(GCC) 4.6.2
/*
* std::vector::emplace_back (since C++11)
*
* Appends a new element to the end of the container.
* The element is constructed in-place, i.e. no copy or move operations are performed.
* The constructor of the element is called with exactly the same arguments,
* as supplied to the function.

https://gist.github.com/juehan/3018058
http://www.cplusplus.com/reference/vector/vector/emplace_back/
http://en.cppreference.com/w/cpp/container/vector/emplace_back

?? whether i add or not std::move seems same effect

g++ -std=c++11 emplaceback.cc -o emplaceback
* */

#include <vector>
#include <iostream>
#include <string>
#include <algorithm>

struct Person
{
    int _age;
    std::string _lname;
    std::string _fname;

    
    Person(int age, std::string&& lname, std::string&& fname) :
        _age(age), _lname(std::move(lname)), _fname(std::move(fname))
    {
        std::cout<<"constructor called"<<std::endl;
    }

    // rvalue
    Person(const Person&& rhs) :
        _age(rhs._age), _lname(std::move(rhs._lname)), _fname(std::move(rhs._fname))
    {
        std::cout<<"move constructor called"<<std::endl;
    }

    //default is an new C++ explicit instruction to the compiler to generate default constructor,
    //copy constructor or assignment operator for a class.

    Person& operator=(const Person& rhs) = default;

};

//compare between std::vector::push_back and std::vector::emplace_back

void TestEmplace()
{
    std::cout<<"# PushBack"<<std::endl;
    std::vector<Person> v;

    //to use push_back, it needs to pass object, thus, construct and move will be called.

    v.push_back(Person(1, "Baby", "Caren"));

    for(Person& p : v)
    {
        std::cout<<p._age<<" : "<<p._fname<<" : "<<p._lname<<std::endl;
    }

    std::cout<<"\n\n# Emplace"<<std::endl;
    std::vector<Person> vEmplace;


    //emplace_back allow you construct on the fly, thus only constructor called. no move.
    // passing in rvalue
    vEmplace.emplace_back(18, "HighTeen", "Caren");

    for(Person& p : vEmplace)
    {
        std::cout<<p._age<<" : "<<p._fname<<" : "<<p._lname<<std::endl;
    }
}

int main()
{
    TestEmplace();
    return 0;
}

/*
Ouput
# PushBack
constructor called
move constructor called
1 : Caren : Baby
# Emplace
constructor called
18 : Caren : HighTeen
Press any key to continue.
*
* */