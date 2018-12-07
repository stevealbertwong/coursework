/*
Binary Heap:
i.e. always sorted binary tree


binary/max/min heap is a sorted(swapped) array	
	=> pop(): swap w last node n bubble down
	=> could function as priority queue
    => HEAP IS NOT A TREE since NOT DIRECTED, IMPLEMENTED IN LINKED NODES


Arr[(i-1)/2]	Returns the parent node (if odd, de)
Arr[(2*i)+1]	Returns the left child node
Arr[(2*i)+2]	Returns the right child node

https://www.geeksforgeeks.org/binary-heap/

g++ 
*/


#include <iostream>
#include <climits>
using namespace std;
 
// Prototype of a utility function to swap two integers
void swap(int *x, int *y);
 
class MinHeap
{
    int *harr; // pointer to array head of elements in heap
    int capacity; // maximum possible size of min heap
    int heap_size; // Current number of elements in min heap
public:
    // Constructor
    MinHeap(int capacity);
 
    // to heapify a subtree with root at given index
    void MinHeapify(int );
    void Heapify_Iteration(int i);
 
    int parent(int i) { return (i-1)/2; }
 
    // to get index of left child of node at index i
    int left(int i) { return (2*i + 1); }
 
    // to get index of right child of node at index i
    int right(int i) { return (2*i + 2); }
 
    // to extract the root which is the minimum element
    int extractMin();
 
    // Decreases key value of key at index i to new_val
    void decreaseKey(int i, int new_val);
 
    // Returns the minimum key (key at root) from min heap
    int getMin() { return harr[0]; }
 
    // Deletes a key stored at index i
    void deleteKey(int i);
 
    // Inserts a new key 'k'
    void insertKey(int k);
    void bubbleUp(int i);
};
 
// Constructor: Builds a heap from a given array a[] of given size
MinHeap::MinHeap(int cap)
{
    heap_size = 0;
    capacity = cap;
    harr = new int[cap];
}
 
// TODO turn while loop into recursion
void MinHeap::insertKey(int k)
{
    if (heap_size == capacity)
    {
        cout << "\nOverflow: Could not insertKey\n";
        return;
    }
 
    // First insert the new key at the end
    heap_size++;
    int i = heap_size - 1;
    harr[i] = k;
 
    // Second BUBBLE UP !!!
    // while (i != 0 && harr[parent(i)] > harr[i])
    // {
    //    swap(&harr[i], &harr[parent(i)]);
    //    i = parent(i);
    // }

    bubbleUp(i);
}

// recursion
void MinHeap::bubbleUp(int i){
    if(i != 0 && harr[parent(i)] > harr[i])
    {
       swap(&harr[i], &harr[parent(i)]);
       i = parent(i);
       bubbleUp(i);
    }   
}

// Decreases priority 
void MinHeap::decreaseKey(int i, int new_val)
{
    harr[i] = new_val;

    // BUBBLE UP
    // while (i != 0 && harr[parent(i)] > harr[i])
    // {
    //    swap(&harr[i], &harr[parent(i)]);
    //    i = parent(i);
    // }

    bubbleUp(i);
}
 
// This function deletes key at index i. It first reduced value to minus
// infinite, then calls extractMin()
void MinHeap::deleteKey(int i)
{
    decreaseKey(i, INT_MIN);
    extractMin();
}

// pop minimum element (or root) from min heap
int MinHeap::extractMin()
{
    if (heap_size <= 0)
        return INT_MAX;
    if (heap_size == 1)
    {
        heap_size--;
        return harr[0];
    }
 
    // Store the minimum value, and remove it from heap
    int root = harr[0];
    harr[0] = harr[heap_size-1]; // grap the last element swap w 1st
    heap_size--;
    // MinHeapify(0);
    Heapify_Iteration(0);
 
    return root;
}

/*
BUBBLE DOWN (swap w most urgent child) - recursion version
	recursively heapify a subtree with a node at given index

1. index of left, right child
2. compare + index of smaller/more urgent
3. swap + recursion

*/
void MinHeap::MinHeapify(int i)
{
    int l = left(i);
    int r = right(i);
    int smallest = i; // index of smaller child

    if (l < heap_size && harr[l] < harr[i])
        smallest = l;
    if (r < heap_size && harr[r] < harr[smallest])
        smallest = r;

    if (smallest != i) // base case, if index didn't get updated
    {
        swap(&harr[i], &harr[smallest]);
        MinHeapify(smallest);
    }
}

void MinHeap::Heapify_Iteration(int i)
{	
	int smallest = i;

	while(1){
		int l = left(i);
    	int r = right(i);
    	    	
    	if (l < heap_size && harr[l] < harr[i])
	        smallest = l;
	    if (r < heap_size && harr[r] < harr[smallest])
	        smallest = r;

	    if (smallest != i) // base case, if index didn't get updated
	    {
	        swap(&harr[i], &harr[smallest]);	        
	    } else {	    	
	    	break; // swapped head bubble down
	    }

	    i = smallest;
	}
}
 
// swap two int array elements
void swap(int *x, int *y)
{
    int temp = *x;
    *x = *y;
    *y = temp;
}
 
// Driver program to test above functions
int main()
{
    MinHeap h(11);
    h.insertKey(3);
    h.insertKey(2);
    h.deleteKey(1);
    h.insertKey(15);
    h.insertKey(5);
    h.insertKey(4);
    h.insertKey(45);
    cout << h.extractMin() << " ";
    cout << h.getMin() << " ";
    h.decreaseKey(2, 1);
    cout << h.getMin();
    return 0;
}