/*
https://stackoverflow.com/questions/18398167/how-to-copy-a-txt-file-to-a-char-array-in-c
https://stackoverflow.com/questions/7241871/loading-a-file-into-a-vectorchar
http://www.cplusplus.com/reference/string/string/c_str/
http://www.cplusplus.com/reference/fstream/ifstream/
https://www.geeksforgeeks.org/operator-overloading-cpp-print-contents-vector-map-pair/
https://stackoverflow.com/questions/6406356/how-to-write-vector-values-to-a-file



NOTICE:
  typedef basic_ifstream<char> ifstream;



read data into array, vector, string

ifstream common methods
  read()
  open()
  isopen()
  eof()

1. entirety e.g. Dorabot RSA
  std::ifstream
  std::string(std::istreambuf_iterator)
  new char(ifs.length()+1)
  strcpy(string.cstr())

2. skip white space, stream operator >>
  "I Like Pie" => "ILikePie"

3. skip line, getline

4. entirety, ifstream.read()

g++ -std=c++14 array_vector_string.cc -o array_vector_string
*/
#define FILE_NAME "test.data"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <list>
#include <iterator>
#include <array>
using namespace std;

char * heap_array;

// operator-overloads couting vector
template <typename T>
ostream& operator<<(ostream& os, const vector<T>& v)
{
    os << "[";
    for (int i = 0; i < v.size(); ++i) {
        os << v[i];
        // if (i != v.size() - 1)
        //     os << ", ";
    }
    os << "]\n";
    return os;
}

// operator-overloads couting list
template <typename T>
std::ostream& operator<<(std::ostream& ostr, const std::list<T>& list)
{
    for (auto &i : list) {
        ostr << " " << i;
    }
    return ostr;
}

/*
alternatively use getline() to read into string
but then it will skip line breaker
*/
void load_skipline_getline_string(std::string filename){
  std::string data_;
  std::string buffer;
  std::ifstream my_file;
  my_file.open(filename);
  while(my_file){
    getline(my_file, buffer);
    data_.append(buffer);
  }

  cout << data_;
  my_file.close();
}

/* myfile >> myArray[i]; 
you are reading file word by word which causes skipping of the spaces.
*/
void load_skipwhitespace_streamop_array(std::string filename){
  int arraysize = 100000;
  // char myArray[arraysize];
  char *myArray = new char[arraysize];
  char current_char;
  int num_characters = 0;
  int i = 0;
  ifstream myfile (filename);
  if (myfile.is_open())
  {
      while ( !myfile.eof())
      {
            myfile >> myArray[i];
            i++;
            num_characters ++;
      }   
  }
  cout << myArray;
}

/************************************************************************/
// ENTIRETY
//
/************************************************************************/
/*
std::istreambuf_iterator iterator is input iterator that read successive elements from a stream buffer.
std::istreambuf_iterator<char>(in) will create iterator for our ifstream in (beginning of the file), 
and if you don't pass any parameters to the constructor, it will create end-of-stream iterator (last position):
So, this will copy all characters, starting from the first in the file, until the next character is end of the stream.

keep line breaker and white space, read entirety

c_str() returns const char *
*/

void load_entirety_strcpy_chararray(std::string filename){
  ifstream in(filename);  
  
  std::string contents((std::istreambuf_iterator<char>(in)), 
      std::istreambuf_iterator<char>());
  heap_array = new char[contents.length()+1];
  std::strcpy(heap_array, contents.c_str());

  cout << heap_array;
}

/*

if (!file.eof() && !file.fail())
{
    file.seekg(0, std::ios_base::end);
    std::streampos fileSize = file.tellg();
    vec.resize(fileSize);

    file.seekg(0, std::ios_base::beg);
    file.read(&vec[0], fileSize);
}

vector by default construct on heap
*/

void load_entirety_chararray_read_vector(std::string filename){
  std::vector<char> vec;
  std::ifstream file(filename);
  // assert(file.is_open());
  while (!(file.eof() || file.fail())) {
    char buffer[100];
    file.read(buffer, 100); // read 100 char/bytes at a time
    cout << buffer;
    vec.insert(vec.end(), buffer, buffer + file.gcount());
  }
  cout << vec;
}

void load_entirety_istreamiter_string_vector(std::string filename){  
  std::ifstream in(filename);

  istream_iterator<char> data(in);
  istream_iterator<char> end;
  // vec.insert( std::back_inserter(vec), data, end );
  // vec.insert(vec.end(), data, end );
  
  std::string contents((std::istreambuf_iterator<char>(in)), 
      std::istreambuf_iterator<char>());

  std::vector<char> vec(contents.begin(), contents.end());
  cout << vec;
}

void load_entirety_istreamiter_copy_backinserter_vector(){
  
  ifstream is("int.txt",ios::in);  

  std::vector<int> result;
  std::copy(std::istream_iterator<int>(is),
            std::istream_iterator<int>(),
            std::back_inserter(result));
  
  for (int i=0; i<result.size(); i++) {
    cout << result[i] << '\n';
  }   
}

/*==================================================================*/


void write_entirety_streamop_vector(){
  std::ofstream f("somefile.txt");
  // for(vector<X>::const_iterator i = v.begin(); i != v.end(); ++i) {
  //   f << *i << '\n';
  // }

  // for (const auto &e : v) outFile << e << "\n";
}

void write_entirety_streamiter_vector(){
    std::vector<std::string> example;
    example.push_back("this");
    example.push_back("is");
    example.push_back("a");
    example.push_back("test");

    std::ofstream output_file("./example.txt");
    std::ostream_iterator<std::string> output_iterator(output_file, "\n");
    std::copy(example.begin(), example.end(), output_iterator);
}


void write_int_vector(){
    std::vector<int> example;
    example.push_back(10);
    example.push_back(2000);
    example.push_back(5);
    example.push_back(976128);

    std::ofstream output_file("./int.txt");
    // ubuntu automatically added -
    std::ostream_iterator<int> output_iterator(output_file, "\n");
    std::copy(example.begin(), example.end(), output_iterator);
}
/*==================================================================*/

void print_entirety(){    
  // prints unedited file 
  // cout << contents; 

  // prints each word
  char * p = std::strtok(heap_array," ");
  while (p!=0)
  {
    std::cout << p << '\n';
    p = std::strtok(NULL," ");
  }
}

void free_entirety(){
  delete[] heap_array;
}




/*==================================================================*/
int main () 
{
  
  
  write_int_vector();





  // load("test.data");
}