/*
http://www.cplusplus.com/reference/vector/vector/vector/
https://stackoverflow.com/questions/2236197/what-is-the-easiest-way-to-initialize-a-stdvector-with-hardcoded-elements

https://www.geeksforgeeks.org/initialize-a-vector-in-cpp-different-ways/

vector of struct* ??
*/

// constructing vectors
#include <iostream>
#include <vector>
#include <iterator>
using namespace std;

void init_push_back(){
      // Create an empty vector
    vector<int> vect; 
    
    vect.push_back(10);
    vect.push_back(20);
    vect.push_back(30);
 
    for (int x : vect)
        cout << x << " ";
}

void init_repeat_elements(){
      int n = 3;
 
    // Create a vector of size n with
    // all values as 10.
    vector<int> vect(n, 10);
 
    for (int x : vect)
        cout << x << " ";
}

void init_curly_bracket(){
      vector<int> vect{ 10, 20, 30 };
 
    for (int x : vect)
        cout << x << " ";
}

void init_from_array(){
      int arr[] = { 10, 20, 30 };
    int n = sizeof(arr) / sizeof(arr[0]);
 
    vector<int> vect(arr, arr + n);
 
    for (int x : vect)
        cout << x << " ";
}

void init_from_vector(){
      vector<int> vect1{ 10, 20, 30 };
 
    vector<int> vect2(vect1.begin(), vect.end());
 
    for (int x : vect2)
        cout << x << " ";
}

/* http://www.cplusplus.com/reference/vector/vector/data/ 
myvector contains: 10 20 0 100 0
*/
void init_from_pointer(){
  std::vector<int> myvector (5);
  int* p = myvector.data();

  *p = 10;
  ++p;
  *p = 20;
  p[2] = 100;

  std::cout << "myvector contains:";
  for (unsigned i=0; i<myvector.size(); ++i)
    std::cout << ' ' << myvector[i];
  std::cout << '\n';
}

/*
https://stackoverflow.com/questions/6399090/c-convert-vectorint-to-vectordouble
*/
void vector_typecast(){
    vector<int> v_int;
    for (int i=0; i<10; ++i) {
        v_int.push_back(i);
    }
    vector<double> v_float(v_int.begin(), v_int.end());
    copy (v_float.begin(), v_float.end(), ostream_iterator<double>(cout, " "));
    cout << endl;
    return 0;
}


void test(){
  // constructors used in the same order as described above:
  std::vector<int> first;                                // empty vector of ints
  std::vector<int> second (4,100);                       // four ints with value 100
  std::vector<int> third (second.begin(),second.end());  // iterating through second
  std::vector<int> fourth (third);                       // a copy of third

  // the iterator constructor can also be used to construct from arrays:
  int myints[] = {16,2,77,29};
  std::vector<int> fifth (myints, myints + sizeof(myints) / sizeof(int) );

  std::cout << "The contents of fifth are:";
  for (std::vector<int>::iterator it = fifth.begin(); it != fifth.end(); ++it)
    std::cout << ' ' << *it;
  std::cout << '\n';

}

int main ()
{


  return 0;
}