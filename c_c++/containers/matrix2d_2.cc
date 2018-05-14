/*
https://stackoverflow.com/questions/13121469/initializing-a-vector-of-vectors-having-a-fixed-size-with-boost-assign
*/
#include <vector>
#include <iostream>
using namespace std;


int main(){
    int n =4; 
    vector<vector<int>> v(n);
    //populate
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            
            v[i].push_back(i + j);
        }
    }
    // display
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            cout << v[i][j] << " ";
        }
        cout << endl;
    }
}