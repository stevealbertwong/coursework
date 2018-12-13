/*
divide and conquer / pivot sort -> recursion

http://www.algolist.net/Algorithms/Sorting/Quicksort
*/

// left, right -> index in array
// base case -> when left index == right index 
void quickSort(int arr[], int left, int right) {

      // 1. pick pivot index
      int i = left, j = right;
      int tmp;
      int pivot = arr[(left + right) / 2];

      // 2. head n end, swap() to pivot left n right
      while (i <= j) {
            // i. move index to 
            while (arr[i] < pivot)
                  i++;
            while (arr[j] > pivot)
                  j--;
            // ii. swap()
            if (i <= j) { 
                  tmp = arr[i];
                  arr[i] = arr[j];
                  arr[j] = tmp;
                  i++;
                  j--;}};

      // 3. recurse if base case not met 
      if (left < j)
            quickSort(arr, left, j);
      if (i < right)
            quickSort(arr, i, right);
}
