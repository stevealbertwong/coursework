/*
http://www.algolist.net/Algorithms/Sorting/Insertion_sort
*/

void insertionSort(int arr[], int length) {

      // i: 1 num at a time as sorted
      // j: index to loop thru sorted 
      int i, j, tmp;

      // 1 num at a time as sorted
      for (i = 1; i < length; i++) {
            j = i;
            // swap() newest num to its pos in sorted
            while (j > 0 && arr[j - 1] > arr[j]) {
                  tmp = arr[j];
                  arr[j] = arr[j - 1];
                  arr[j - 1] = tmp;
                  j--;
            }
      }
}

