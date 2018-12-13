/* http://www.algolist.net/Algorithms/Sorting/Selection_sort
*/


void selectionSort(int arr[], int n) {
      
      // i: 1st element of unsorted part
	  // j: minimal element in the unsorted part
      int i, j, minIndex, tmp;    
      
      for (i = 0; i < n - 1; i++) {
            minIndex = i;
            // look for smallest num's index
            for (j = i + 1; j < n; j++)
                  if (arr[j] < arr[minIndex])
                        minIndex = j;
            // swap()
            if (minIndex != i) {
                  tmp = arr[i];
                  arr[i] = arr[minIndex];
                  arr[minIndex] = tmp;
            }
      }
}