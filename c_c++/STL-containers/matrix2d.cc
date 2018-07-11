/*
https://stackoverflow.com/questions/13121469/initializing-a-vector-of-vectors-having-a-fixed-size-with-boost-assign
https://stackoverflow.com/questions/21663256/how-to-initialize-a-vector-of-vectors-on-a-struct
*/


#include <iostream>
#include <vector>
using namespace std;

int main(int argc, char const *argv[])
{
	int n(5), m(8);
	// vector<vector<int> > mat(n, vector<int>(m));
	vector<vector<int> > mat(6, vector<int>(6));

	// mat[0][0] =4; //direct assignment OR

	// for (int i=0;i<n;++i)
	//     for(int j=0;j<m;++j){
	//         mat[i][j] = rand() % 10;
	//     }
	return 0;
}
