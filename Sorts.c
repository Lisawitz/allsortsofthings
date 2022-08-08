#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <unistd.h>

// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

void initializeRandomArray(int array[], int size) {
    srand(time(NULL));
    for(int i = 0; i < size; i++) {
        array[i] = rand() % 500;
    }
}

void printArray(int array[], int size) {
    for(int i = 0; i < size; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
}

void swap(int array[], int indexA, int indexB) {
    int tmp = array[indexA];
    array[indexA] = array[indexB];
    array[indexB] = tmp;
}

// used in Merge Sort
void merge(int array[], int size, int first, int mid, int last) {
    int tmpArray[size];
    int firstL = first;
    int lastL = mid;
    int firstR = mid + 1;
    int lastR = last;

    int index = firstL;

    // choose the smaller element
    for(; firstL <= lastL && firstR <= lastR; ++index) {
        tmpArray[index] = (array[firstL] < array[firstR]) ? array[firstL++] : array[firstR++];
    }

    // use up left array if longer than right array
    for(; firstL <= lastL; ++firstL, ++index) { 
        tmpArray[index] = array[firstL];
    }

    // use up left array if longer than right array
    for(; firstR <= lastR; ++firstR, ++index) { 
        tmpArray[index] = array[firstR];
    }

    // copy to original array
    for(index = first; index <= last; ++index) {
        array[index] = tmpArray[index];
    }
}

// used in Quick Sort
int partition(int array[], int first, int last) {
    int pivot = array[last];
    int pivotIndex = first;
    for(int i = first; i < last; i++) {
        if(array[i] <= pivot) {
            swap(array, i, pivotIndex);
            pivotIndex++;
        }
    }
    swap(array, pivotIndex, last);
    return pivotIndex;
}

// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

// Selection Sort
// Repeatedly find smallest element from unsorted subarray and move to beginning of sorted subarray.
// Time Complexity: O(N^2)
// Space Complexity (memory for swapping) O(1)
void selectionSort(int array[], int size) {
    for(int i = 0; i < size - 1; i++) {
        int minPos = i;
        for(int j = i + 1; j < size; j++) {
            if(array[j] < array[minPos]) {
                minPos = j;
            }
        }
        swap(array, i, minPos);
    }
}

// Insertion Sort
// Involves inserting values and shifting them. 
// Considered better than Selection Sort and Bubble Sort because the number of comparisons and shifts
// are comparitively a lot less.
// Time Complexity: O(N^2)
// Average case: O(N^2)
// Worst case: O(N^2)
void insertionSort(int array[], int size) {
    for(int i = 1; i < size; i++) {
        int tmp = array[i];
        int tmpIndex = i;
        while(tmpIndex > 0 && array[tmpIndex - 1] > tmp) {
            array[tmpIndex] = array[tmpIndex - 1];
            tmpIndex = tmpIndex - 1;
        }
        array[tmpIndex] = tmp;
    }
}

// Bubble Sort
// Improved to only continue if a swap occured in the inner loop (because otherwise the array is sorted).
// Time Complexity: O(N^2)
// Best case: O(N)
// Average case: O(N^2)
// Worst case: O(N^2) (elements arranged in decreasing order)
// Space Complexity (memory for swapping) O(1)
void bubbleSort(int array[], int size) {
    for(int i = 1; i < size; i++) {
        int swapped = 0;
        for(int j = 0; j < size - 1; j++) {
            if(array[j] > array[j + 1]) {
                swap(array, j, j + 1);
                swapped = 1;
            }
        }
        if(swapped == 0) {
            break;
        }
    }
}

// Shell Sort
// A variation of Insertion Sort.
// Space Complexity: O(1)
// Time Complexity: O(N^2)
// Best Case: (already sorted) O(Nlog(N))
// Average Case: O(Nlog(N)^2)
// Worst Case: O(N^2)
void shellSort(int array[], int size) {
    for(int gap = size / 2; gap > 0; gap /= 2) {
        for(int i = gap; i < size; i++) {
            int tmp = array[i];
            int j;
            for(j = i; j >= gap && array[j - gap] > tmp; j -= gap) {
                array[j] = array[j - gap];
            }
            array[j] = tmp;
        }
    }
}

// Merge Sort 
// Recursively divide and conquer.
// Time Complexity: O(Nlog(N)) (among all cases)
// Best Case: O(Nlog(N)) 
// Average Case: O(Nlog(N))
// Worst Case: O(Nlog(N))
// Space Complexity: O(N)
void mergeSort(int array[], int size, int first, int last) {
    if(first >= last) { // base case
        return;
    }
    int mid = (first + last) / 2;
    mergeSort(array, size, first, mid);
    mergeSort(array, size, mid + 1, last);
    merge(array, size, first, mid, last);
}

// Quick Sort
// Like Merge Sort, recursively divide and conquer. Unlike Merge Sort, preferred since it is an in-place
// sort with space complexity O(1).
// Time Complexity: O(N^2)
// Best Case: O(Nlog(N)) 
// Average Case: O(Nlog(N))
// Worst Case: O(N^2)
// Space Complexity: O(1)
void quickSort(int array[], int size, int first, int last) {
    if(first >= last) { // base case
        return;
    }
    int pivotIndex = partition(array, first, last);
    quickSort(array, size, first, pivotIndex - 1);
    quickSort(array, size, pivotIndex + 1, last);
}

// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

int main() {
    struct timeval startTime, endTime;
    int size = 500;
    int array1[size];
    initializeRandomArray(array1, size);
    printArray(array1, size);
    gettimeofday(&startTime, NULL);
    quickSort(array1, size, 0, size - 1);
    gettimeofday(&endTime, NULL);
    printArray(array1, size);
    printf("\nTime taken (microseconds): %ld \n", (endTime.tv_sec - startTime.tv_sec) * 1000000 + (endTime.tv_usec - startTime.tv_usec));
    return 0;
}

