/*
https://www.geeksforgeeks.org/implementing-hash-table-open-addressing-linear-probing-cpp/

array of linked list
hash table == unordered map

g++ -std=c++11 -g -O0 -Wnull-conversion hashtable_separated_chain.cc -o hashtable_separated_chain
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
            this->key = key;
            this->next = NULL;} 

        V value; 
        K key; 
        HashNode *next; // next bucket
}; 

template<typename K, typename V> // new HashMap<int, int>; 
class HashMap {       
    
    private: 
        HashNode<K,V> **table; // array of linked node
        int tableSize;     
        int size = 0;
        HashNode<K,V> *dummy; //  deleteNode() bug

    public: 
        HashMap(int tableSize = 10){             
            table = new HashNode<K,V>*[tableSize]; // init array                        
            this->tableSize = tableSize;                
            for(int i=0 ; i < tableSize ; i++) 
                table[i] = NULL;
        } 
                
        ~HashMap(){
            for (int i = 0; i < tableSize; ++i){
                if(table[i]!=NULL){
                    HashNode<K,V> *cur = table[i];
                    HashNode<K,V> *prev = NULL;
                    while(cur!=NULL){
                        prev = cur;
                        cur = cur->next;
                        delete prev; // linked list
                    }
                    table[i] = NULL; // table is array of pointers !!
                }
            }            
        }

        int hashCode(K key) { // hashed bucket
            // return key % tableSize; 
            return key % tableSize; // -ve num, unordered_map
        }           

        void insertNode(K key, V value) { // linear probing
            cout << "key : "  << key << " value : " << value << endl;
            HashNode<K,V> *newValue = new HashNode<K,V>(key, value); 
                          
            int bucket = hashCode(key); 
            HashNode<K, V> *bucketList = table[bucket];
            HashNode<K, V> *pre = NULL;

            if (bucketList == NULL){ // if bucket has no entry yet
                cout << "new bucket, no collision" << endl;
                table[bucket] = newValue;
                cout << "inserted : " << newValue->key << endl;

            } else { // if collide, traverse bucket list, attach at end
                cout << "bucket collision" << endl;
                while(bucketList != NULL && bucketList->key != key){
                    pre = bucketList; // keep parent
                    bucketList = bucketList->next;                    
                }

                if (bucketList == NULL){ // no duplicate in bucket list                                                                                
                    cout << "no duplicate in bucket list" << endl;
                    pre->next = newValue; 

                }else{ // if duplicate found, update key to new value
                    cout << "yes duplicate in bucket list" << endl;
                    bucketList->value = value;
                }   

            }            
        } 
          
        bool deleteNode(int key){
            int bucket = hashCode(key); 
            if(table[bucket] != NULL) {                                         
                HashNode<K, V> *cur = table[bucket];
                HashNode<K, V> *prev = NULL;
                
                while(cur!=NULL){ // traverse bucket list
                    if(cur->key == key){                        
                        cout << "deleted value : " << cur->value << endl;
                        // prev entry points to next entry
                        prev->next = cur->next; 
                        delete cur;
                        return true;                        
                    }                                              
                    prev = cur;
                    cur = cur->next;
                }
                return false; // bucket list does not contain
            } else { // bucket does not exist
                return false;     
            }   
        }


        V get(int key){
            int bucket = hashCode(key); 
            if(table[bucket] != NULL) {                                         
                HashNode<K, V> *cur = table[bucket];
                while(cur!=NULL){ // traverse bucket list
                    if(cur->key == key){
                        return cur->value;
                    }                                              
                    cur = cur->next;
                }
                return NULL; // bucket list does not contain
            } else { // bucket does not exist
                return NULL;     
            }                        
        }

        V operator[](int i) {return get(i);}        

        void display() {             
            for(int i=0 ; i<tableSize ; i++) { // each bucket
                if(table[i] != NULL) {                                         
                    HashNode<K, V> *cur = table[i];
                    while(cur!=NULL){                                                
                        cout << "key = " << cur->key  
                             <<"  value = "<< cur->value << endl;                                                 
                        cur = cur->next;
                    }
                }
            } 
        }      
}; 

int main() { 

    HashMap<int, int> h = HashMap<int, int>(); 
    h.insertNode(1,1); 
    h.insertNode(2,3); 
    h.insertNode(1,65); 
    h.insertNode(11,45); 
    h.insertNode(21,23); 
    h.insertNode(31,93); 
    h.display();

    cout << h.get(1) << endl; 
    cout << h[1]<< endl; 
    cout << h[2]<< endl; 
    cout << h.deleteNode(21) << endl; 
    h.display();

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