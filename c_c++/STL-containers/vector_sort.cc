/*
http://www.cplusplus.com/reference/algorithm/sort/
*/
// sort algorithm example
#include <iostream>     // std::cout
#include <algorithm>    // std::sort
#include <vector>       // std::vector

// operator-overloads couting list
std::ostream& operator<<(std::ostream& ostr, const std::vector<int>& v)
{
    for (auto &i : v) {
        ostr << " " << i;
    }
    return ostr;
}


bool smaller_comparison_predicate (int i,int j) { return (i<j); }


struct myclass {
  bool operator() (int i,int j) { return (i<j);}
} myobject;



struct greater_comparison_predicate_functor
{
    template<class T>
    bool operator()(T const &a, T const &b) const { return a > b; }
};





int main () {
  int myints[] = {32,71,12,45,26,80,53,33};
  std::vector<int> myvector (myints, myints+8);               // 32 71 12 45 26 80 53 33

  // using default comparison (operator <):
  std::sort (myvector.begin(), myvector.begin()+4);           //(12 32 45 71)26 80 53 33

  // using function as comp
  std::sort (myvector.begin()+4, myvector.end(), greater_comparison_predicate); // 12 32 45 71(26 33 53 80)

  // using object as comp
  std::sort (myvector.begin(), myvector.end(), myobject);     //(12 26 32 33 45 53 71 80)

  std::sort (myvector.begin(), myvector.end(), greater_comparison_predicate_functor());

  // print out content:
  std::cout << "myvector contains:";
  for (std::vector<int>::iterator it=myvector.begin(); it!=myvector.end(); ++it)
    std::cout << ' ' << *it;
  std::cout << '\n';

  return 0;
}