
// its guranteed each round, largest element to the end
// but not gurnteed smallest element to the top

// n == size of array
void bubbleSort(int arr[], int n) {
      bool swapped = true;
      int j = 0;
      int tmp;
      while (swapped) {
            swapped = false;
            j++; // n-j: max num times to run swap()
            for (int i = 0; i < n - j; i++) {
                  // swap() if next number bigger
                  if (arr[i] > arr[i + 1]) {
                        tmp = arr[i];
                        arr[i] = arr[i + 1];
                        arr[i + 1] = tmp;
                        swapped = true;
                  }
            }
      }
}