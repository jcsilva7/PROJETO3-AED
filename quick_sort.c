#include "swap.h"
#include "quick_sort.h"
#include "insertion.h"

int partition(int arr[], int low, int high){
    int pivot = median_of_three(arr, low, high);
    
    int i = low - 1;

    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    
    swap(&arr[i + 1], &arr[high]);  
    return i + 1;
}

// Mediana de três para escolher o pivô
int median_of_three(int arr[], int low, int high){
    int mid = low + (high - low) / 2;

    if (arr[mid] < arr[low])
        swap(&arr[low], &arr[mid]);
    if (arr[high] < arr[low])
        swap(&arr[low], &arr[high]);
    if (arr[high] < arr[mid])
        swap(&arr[mid], &arr[high]);

    // Move o pivô (mediana) para o fim
    swap(&arr[mid], &arr[high]);
    return arr[high];
}

void quick_sort(int array[], int low, int high){
    if (high - low <= CUTOFF) {
        insertion_sort(array, low, high);
        return;
    }

    if (low < high) {
        int pi = partition(array, low, high);
        quick_sort(array, low, pi - 1);
        quick_sort(array, pi + 1, high);
    }
}