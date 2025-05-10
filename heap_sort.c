#include <stdlib.h>
#include "swap.h"

void heapify(int array[], int size, int i){
    int largest = i;  
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    // If left child is larger than root
    if (left < size && array[left] > array[largest])
        largest = left;

    // If right child is larger than largest so far
    if (right < size && array[right] > array[largest])
        largest = right;

    // If largest is not root
    if (largest != i) {
        swap(&array[i], &array[largest]);

        // Recursively heapify the sub-"tree"
        heapify(array, size, largest);
    }
}

void heap_sort(int array[], int size){
    for (int i = size / 2 - 1; i >= 0; i--)
        heapify(array, size, i);

    // One by one extract an element from heap
    for (int i = size - 1; i > 0; i--) {
        // Move current root to end
        swap(&array[0], &array[i]);

        // call max heapify on the reduced heap
        heapify(array, i, 0);
    }
}