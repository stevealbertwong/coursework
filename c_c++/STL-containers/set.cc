/*
https://thispointer.com/stdset-tutorial-part-1-set-usage-details-with-default-sorting-criteria/

Output:
Set Size = 3
first second third
‘first’ found
‘fourth’ not found
first second third
first second

Number 2 inserted sucessfuly
Number 3 inserted sucessfuly
Number 2 was already present in set
Number 1 inserted sucessfuly
3
1 2 3


https://www.geeksforgeeks.org/set-in-cpp-stl/




g++ -std=c++14 set.cc -o set



you cannot modify the elements using iterators because if you modify the element value 
then internal data structure of std::set will get corrupt and it will not remain balanced binary search tree.

*/

#include <iostream>
#include <set>
#include <string>
#include <iterator> 
using namespace std; 

void checkAndInsert(int num, std::set<int> setOfNumbers)
{
  if(setOfNumbers.insert(num).second)
     std::cout<<"Number "<<num<<" inserted sucessfuly\n";
 else
     std::cout<<"Number "<<num<<" was already present in set\n";
 
}

void thispointer_demo_insert(){
	std::set<int> setOfNumbers;

	checkAndInsert(2, setOfNumbers);
    checkAndInsert(3, setOfNumbers);
    checkAndInsert(2, setOfNumbers);
    checkAndInsert(1, setOfNumbers);
 
   // Check the size of set
   std::cout<<setOfNumbers.size()<<std::endl;
 
   // Iterate through all the elements in a set and display the value.
   for (std::set<int>::iterator it=setOfNumbers.begin(); it!=setOfNumbers.end(); ++it)
      std::cout << ' ' << *it;
   std::cout<<"\n";

}

void thispointer_demo(){
	std::set<std::string> setOfNumbers;
 	
 	// insert()
	setOfNumbers.insert("first");
	setOfNumbers.insert("second");
	setOfNumbers.insert("third");
	setOfNumbers.insert("first"); // duplicate
 
	// size() -> 3
	std::cout<<"Set Size = "<<setOfNumbers.size()<<std::endl;
 
	// iterate 
	std::set<std::string>::iterator it;
	for (it=setOfNumbers.begin(); it!=setOfNumbers.end(); ++it)
	    std::cout << ' ' << *it;
	std::cout<<"\n";

	// find()
	it = setOfNumbers.find("second");
	if(it != setOfNumbers.end())
		std::cout<<"'first'  found"<<std::endl;
	else
		std::cout<<"'first' not found"<<std::endl;
 	
 	// erase()
	setOfNumbers.erase("third");
}



void geeksforgeeks(){
	// sorted set 
    set <int, greater <int> > gquiz1;         
     
    gquiz1.insert(40); 
    gquiz1.insert(30); 
    gquiz1.insert(60); 
    gquiz1.insert(20); 
    gquiz1.insert(50); 
    gquiz1.insert(50); // duplicate
    gquiz1.insert(10); 
  
    // printing sorted set gquiz1 
    set <int, greater <int> > :: iterator itr; 
    cout << "\nThe set gquiz1 is : "; 
    for (itr = gquiz1.begin(); itr != gquiz1.end(); ++itr) 
    { 
        cout << '\t' << *itr; 
    } 
    cout << endl; 
  
    // assign gquiz1 to unsorted gquiz2 
    set <int> gquiz2(gquiz1.begin(), gquiz1.end()); 
  
    // print all elements of the set gquiz2 
    cout << "\nThe set gquiz2 after assign from gquiz1 is : "; 
    for (itr = gquiz2.begin(); itr != gquiz2.end(); ++itr) 
    { 
        cout << '\t' << *itr; 
    } 
    cout << endl; 
  
    // remove all elements up to 30 in gquiz2 
    cout << "\ngquiz2 after removal of elements less than 30 : "; 
    gquiz2.erase(gquiz2.begin(), gquiz2.find(30)); 
    for (itr = gquiz2.begin(); itr != gquiz2.end(); ++itr) 
    { 
        cout << '\t' << *itr; 
    } 
  
    // remove element with value 50 in gquiz2 
    int num; 
    num = gquiz2.erase (50); 
    cout << "\ngquiz2.erase(50) : "; 
    cout << num << " removed \t" ; 
    for (itr = gquiz2.begin(); itr != gquiz2.end(); ++itr) 
    { 
        cout << '\t' << *itr; 
    } 
  
    cout << endl; 
  
    //lower bound and upper bound for set gquiz1 
    cout << "gquiz1.lower_bound(40) : "
         << *gquiz1.lower_bound(40) << endl; 
    cout << "gquiz1.upper_bound(40) : "
         << *gquiz1.upper_bound(40) << endl; 
  
    //lower bound and upper bound for set gquiz2 
    cout << "gquiz2.lower_bound(40) : "
         << *gquiz2.lower_bound(40) << endl; 
    cout << "gquiz2.upper_bound(40) : "
         << *gquiz2.upper_bound(40) << endl; 
}

int main()
{
	// thispointer_demo();
	geeksforgeeks();


	return 0;
}