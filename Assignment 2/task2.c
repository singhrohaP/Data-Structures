#include <stdio.h>
#include "t2.h"

int number_comparisons = 0;
int number_swaps = 0;


void selectionSort(int arr[], int size)
{
    for(int j=0; j<size; j++){
        int min = j;
        for(int i = j+1; i<size; i++){
            number_comparisons++;
            if(arr[i]<arr[min]){
                min = i;
            }
        }
        int tmp = arr[j];
        arr[j] = arr[min];
        arr[min] = tmp;
        number_swaps++;
    }
}



void insertionSort(int arr[], int size)
{
    for(int i = 0; i<size; i++){
        int first = arr[i];
        int j = i-1;
        while (j>=0 && first<arr[j]) {
            number_comparisons++;
            arr[j+1] = arr[j];
            number_swaps++;
            --j;
        }
        arr[j+1] = first;
        number_comparisons++;
    }
}

void swap(int* a, int* b)
{
    int t = *a;
     *a = *b;
     *b = t;
}


int partition(int array[], int beg, int end){
    int pivotIndex = array[end];
    int pIndex= beg-1;
    for(int i =beg; i<end; i++){
        
        if(array[i] < pivotIndex){
            pIndex++;
            swap(&array[pIndex], &array[i]);
            number_swaps++;
        }
        number_comparisons++;
    }
    swap(&array[pIndex+1], &array[end]);
    number_swaps++;
    return pIndex+1;
}

void qSort(int array[], int beg, int end){
    if(beg<end){
        int pivotIndex = partition(array, beg, end);
        qSort(array, beg, pivotIndex-1);
        qSort(array, pivotIndex+1, end);
    }
}

void quickSort(int arr[], int size)
{
    qSort(arr, 0, size-1);
}
