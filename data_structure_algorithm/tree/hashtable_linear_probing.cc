/*
https://www.geeksforgeeks.org/implementing-hash-table-open-addressing-linear-probing-cpp/

array of linked node
hash table == unordered map

TODO:
1. deleteNode() bug -> infinite loop 
2. if table full, extend table size
3. destructor

g++ -std=c++11 -g -O0 -Wnull-conversion hashtable_linear_probing.cc -o hashtable_linear_probing
*/

#include <iostream>
#include <math.h>
// #include </Users/SteveAndrewWong/stdc++.h> 
using namespace std; 

template<typename K, typename V> // new HashNode<K,V>*[tableSize];
class HashNode { // linked node, not linked list if linear probing 
    public:
        HashNode(K key, V value) { 
            this->value = value; 
            this->key = key;} 

        V value; 
        K key; 
}; 

template<typename K, typename V> // new HashMap<int, int>; 
class HashMap {       
    
    private: 
        HashNode<K,V> **table; // array of linked node
        int tableSize;     
        int size = 0;
        HashNode<K,V> *dummy; //  deleteNode() bug

    public: 
        HashMap(int tableSize = 20){             
            table = new HashNode<K,V>*[tableSize]; // init array                        
            this->tableSize = tableSize;                
            for(int i=0 ; i < tableSize ; i++) 
                table[i] = NULL;                           
            dummy = new HashNode<K,V>(-1, -1); // deleteNode() bug
        } 
        
        int hashCode(K key) { // hashed bucket
            // return key % tableSize; 
            return key % tableSize; // -ve num, unordered_map
        }           

        void insertNode(K key, V value) { // linear probing
            HashNode<K,V> *newValue = new HashNode<K,V>(key, value); 
                          
            int bucket = hashCode(key); 
              
            // linear probing
            while(table[bucket] != NULL && table[bucket]->key != key 
                   && table[bucket]->key != -1) { 
                bucket++; 
                bucket %= tableSize; 
            } 
                          
            if(table[bucket] == NULL || table[bucket]->key == -1) 
                size++; // if new key, insert, if existing, overwrite
            
            table[bucket] = newValue; 
        } 
          
        
        V deleteNode(int key) {             
            int bucket = hashCode(key);                           
            while(table[bucket] != NULL) {                 
                if(table[bucket]->key == key) // if found
                { 
                    HashNode<K,V> *temp = table[bucket];                                           
                    table[bucket] = dummy; // why not just nullptr ?? BUG infinite loop
                    size--; 
                    return temp->value; 
                } 
                bucket++; 
                bucket %= tableSize;       
            }                           
            return NULL; 
        } 
                  
        V get(int key) {             
            int bucket = hashCode(key); 
            int counter=0;             
            while(table[bucket] != NULL) {    
                int counter =0; 
                if(counter++>tableSize)  //to avoid infinite loop 
                    return NULL;                         
                if(table[bucket]->key == key) // if found
                    return table[bucket]->value; 
                bucket++; 
                bucket %= tableSize; 
            }                           
            return NULL; 
        } 

        V operator[](int i) {return get(i);}        

        void display() { 
            for(int i=0 ; i<tableSize ; i++) { 
                if(table[i] != NULL && table[i]->key != -1) 
                    cout << "key = " << table[i]->key  
                         <<"  value = "<< table[i]->value << endl; 
            } 
        }      
}; 

int main() { 

    HashMap<int, int> h = HashMap<int, int>(); 
    h.insertNode(1,1); 
    h.insertNode(2,3); 
    h.display();     
    cout << h.get(1) << endl; 
    cout << h[1]<< endl; 
    cout << h[2]<< endl; 
    cout << h.deleteNode(2) << endl; 

    // HashMap<int, int> *h = new HashMap<int, int>(100); // default table size 20
    // HashMap<int, int> *h = new HashMap<int, int>; 
    // h->insertNode(1,1); 
    // h->insertNode(2,2); 
    // h->insertNode(2,3); 
    // h->display();     
    // cout << h->deleteNode(2) << endl; 
    // cout << h->get(2) << endl; 
    // cout << h->get(1) << endl; 
    // cout << h[1] << endl; 
      
    return 0; 
} 