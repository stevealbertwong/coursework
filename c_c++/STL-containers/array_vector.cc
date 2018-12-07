/*
vector to array
array to vector
typecast vector
typecast vector to byte array ??

https://en.cppreference.com/w/c/language/array_initialization
*/

#include <cstdlib>
#include <cstring>
#include <string>
#include <iostream>
#include <fstream>
#include <thread>
#include <chrono>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/select.h>
#include <netdb.h>
#include <unistd.h>

using namespace std;

void arr2vec_constructor_pointer_arithmetic(){
    int arr[] = { 10, 20, 30 };
    int n = sizeof(arr) / sizeof(arr[0]);
 
    vector<int> vect(arr, arr + n);
 
    for (int x : vect)
        cout << x << " ";
}

/*
http://www.cplusplus.com/reference/algorithm/copy/
deep copy
*/
void arr2vec_copy(){
	int myints[]={10,20,30,40,50,60,70};
	std::vector<int> myvector (7);
	std::copy ( myints, myints+7, myvector.begin() );
	std::cout << "myvector contains:";
	for (vector<int>::iterator it = myvector.begin(); it!=myvector.end(); ++it)
	std::cout << ' ' << *it;
	std::cout << '\n';
}

/*
http://www.cplusplus.com/forum/general/62900/
*/
void arr2vec_insert(){
	float data_f[10] = { 1.1 ,  1.2 , 1.3 , 1.4 , 1.5 , 1.6 , 1.7 , 1.8 , 1.9 , 1.0 } ; 
	vector<float> float_vect; 
	float_vect.insert( float_vect.being() , data_f , data_f + 10 ) ; 
	for(int i = 0 ; i < 10; i++ ) 
		cout<< "\n Vector = " << float_vect[i] ;
}

/*
http://www.cplusplus.com/reference/vector/vector/data/
https://www.experts-exchange.com/questions/27608887/reinterpret-cast-from-C-vector-to-byte-array-and-vise-versa-Is-this-possible.html
https://stackoverflow.com/questions/2923272/how-to-convert-vector-to-array
*/
void vec2arr_vector_pointer(){
	vector<unsigned char> v{10, 20, 30};
	vector<unsigned char>::pointer p = &v[0];
	// compatible, identical types - defined as 'Pointer to T'
	unsigned char* aByteArray = p; 
	unsigned char* p2 = v.data(); // data() return head of linked list
	std::cout << p2[2] << std::endl;
}

void vec2arr_memcpy(){
	// shallow copy
	// int *destination = new int(10);
	int dest[10] = {0}; // 10 zeros
	int y[10] = {1,2,3}; // 1 2 3 0 0 0 ....
	int x[] = {1,2,3}; // x has type int[3] and holds 1,2,3
	std::vector<int> myvector{10,20,30,40,50,60,70};

	memcpy( dest, &myvector[0], sizeof( int ) * myvector.size() );

	std::cout << "myvector contains:";
	for (std::vector<int>::iterator it = myvector.begin(); it!=myvector.end(); ++it)
	std::cout << ' ' << *it;
	std::cout << '\n';
}

void vec2arr_cpy(){
	int arr[100];
	std::vector<int> v{10,20,30,40,50,60,70};
	std::copy(v.begin(), v.end(), arr);
}

void vec2arr_forloop_index(){
	vector<int> vect0r;
    int array[100];
    for(int i = 0; i < 10 ; i++) vect0r.push_back( i ) ;
    for(i = 0; i < vect0r.size(); i++) array[i] = vect0r[i];
    for(i = 0; i < vect0r.size(); i++)  cout<< array[i] <<" \n";
    cout<<" \n";
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

int main(int argc, char const *argv[])
{

	return 0;
}