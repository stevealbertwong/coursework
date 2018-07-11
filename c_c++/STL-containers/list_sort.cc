/*
http://www.cplusplus.com/reference/list/list/sort/
https://en.cppreference.com/w/cpp/container/list/sort
http://www.cs.northwestern.edu/~riesbeck/programming/c++/stl-summary.html#list

https://stackoverflow.com/questions/10652674/sorting-stdlists-using-stdsort


*/

// list::sort
#include <iostream>
#include <list>
#include <string>
#include <cctype>
#include <functional>
#include <list>


// operator-overloads couting list
std::ostream& operator<<(std::ostream& ostr, const std::list<int>& list)
{
    for (auto &i : list) {
        ostr << " " << i;
    }
    return ostr;
}


// functor, std::sort(v.begin(), v.end(), greater());
struct greater_comparison_predicate_functor
{
    template<class T>
    bool operator()(T const &a, T const &b) const { return a > b; }
};

bool greater_comparison_predicate(int i,int j) { return (i<j); }

// comparison predicate, not case sensitive.
bool compare_nocase (const std::string& first, const std::string& second)
{
  unsigned int i=0;
  while ( (i<first.length()) && (i<second.length()) )
  {
    if (tolower(first[i])<tolower(second[i])) return true;
    else if (tolower(first[i])>tolower(second[i])) return false;
    ++i;
  }
  return ( first.length() < second.length() );
}

int main ()
{

	// string list sorting
	std::list<std::string> stringlist;
	std::list<std::string>::iterator it;
	stringlist.push_back ("one");
	stringlist.push_back ("two");
	stringlist.push_back ("Three");

	stringlist.sort();

	std::cout << "stringlist contains:";
	for (it=stringlist.begin(); it!=stringlist.end(); ++it)
	std::cout << ' ' << *it;
	std::cout << '\n';

	stringlist.sort(compare_nocase);

	std::cout << "stringlist contains:";
	for (it=stringlist.begin(); it!=stringlist.end(); ++it)
	std::cout << ' ' << *it;
	std::cout << '\n';

	// int list sorting
	std::list<int> intlist = { 8,7,5,9,0,1,3,2,6,4 };
	std::cout << "before:     " << intlist << "\n";
	intlist.sort();
	std::cout << "ascending:  " << intlist << "\n";
	intlist.sort(std::greater<int>());
	std::cout << "descending: " << intlist << "\n";


	// CANNOT USE ALGO::SORT ON LIST => list does not have random access iterator 
	// std::sort requires iterators to be random access, and std::list iterators are only bidirectional.
	// since linked list not contagious memory
	// std::sort certainly doesn't work on associative containers 
	// Associative containers are accessed by key, not by position.
	std::list<int> intlist2 = { 8,7,5,9,0,1,3,2,6,4 };
	// std::sort(intlist2.begin(), intlist2.end(), greater_comparison_predicate_functor());
	// std::cout << "descending:  " << intlist2 << "\n";


  return 0;
}