#ifndef QUICK_SORT_H
#define QUICK_SORT_H

#define CUTOFF 10

int median_of_three(int arr[], int low, int high);
int partition(int arr[], int low, int high);
void quick_sort(int array[], int low, int high);

#endif