/*******************************
 * David Tran/Toan Nguyen
 * CMPE 130
 * quick_sort.cpp
 * November 30, 2017
 *******************************/
#include<stdio.h>

using namespace std;

void swap (int *first, int *second) //helper function to swap values in array
{                                   //can change int to class Item or whatever type is needed
    int start = *first;
    *first = *second;
    *second = start;
}

int partition (int arr[], int low, int high) //arr[] is sorted array, low is start index, and high is end index
{
    int pivot = arr[(high-low)/2];  //set pivot as middle element
    int index = (low - 1);          //set index to start at lower element

    for (int i = low; i <= high - 1; i++)
    {
        if (arr[i] <= pivot)            //if element is smaller than pivot
        {
            index++;                    //increment index
            swap(&arr[index], &arr[i]);
        }
    }
    //swap(&arr[i + 1], &arr[high]);
    //return (i + 1);
}

void quickSort (int arr[], int low, int high)
{
    if (low < high)                     //if unsorted array
    {
        int partitionIndex = partition(arr, low, high);

        quickSort(arr, low, partitionIndex - 1);
        quickSort(arr, partitionIndex + 1, high);
    }

}
