#include <stdio.h> 
#include "t2.h"

int number_comparisons = 0;
int number_swaps = 0;

void swap(int *a, int *b){
  //I have called swap function in every sorting function, thus incremented its count here only.
  int temp = *a;
  *a = *b;
  *b = temp;
  number_swaps++;
}

void selectionSort(int arr[], int size) 
{ 
  int j, k;
  for(int i = 0; i < size - 1; i++ ){ //first loop is for the passes
    for(j=k=i; j < size; j++){  //this loop compares i-th element to every other element in the array
      number_comparisons++; //as comparision is taking place every iteration of this function
      if(arr[j] < arr[k]){
        k = j;
      }
    }
    swap(&arr[i], &arr[k]);
  }
} 

void insertionSort(int arr[], int size) 
{ 
  int j = 0, x = 0;
  for(int i = 1; i < size; i++ ){ // For the passes of insertion sort
    j = i - 1;
    x = arr[i];
    while(j > -1 && arr[j] > x){ //insertion sort logic - comparing with every previous element and swapping if it is greater than the current element
      number_comparisons++;
      swap(&arr[j+1], &arr[j]);
      j--;
    }
    //if the current element is greater than element at j - the above loop would not run but a comparision has taken place.
    if(x > arr[j])
    number_comparisons++;
  }
}

int partition(int arr[], int low, int high){
  //Low is the only pivot element that was working with this quick sort implementation
  int pivot = arr[low];
  int i = low, j = high + 1;
  do{
    //Scanning from the left side of the array
    do
    {
      //Number of comparisons will increment at every iteration
      i++;
      number_comparisons++;
    } while (arr[i] <= pivot);
    //Scanning from the right side of the array
    do
    {
      //Number of comparisons will increment at every iteration
      j--;
      number_comparisons++;
    } while(arr[j] > pivot);
    //If there are two elements (ith and jth) at their wrong positions, swapping of these locations must take place.
    if(i < j) swap(&arr[i], &arr[j]);
  } while(i < j);
  // Swapping of the element at index low and j to put the element at low at the correct position at j
  swap(&arr[low], &arr[j]);
  return j;
}

void quickSortActual(int arr[], int low, int high){
  int j;
  if(low < high){
    j = partition(arr, low, high);//Every time the element at the index low gets sorted to position j
    quickSortActual(arr, low, j-1);//Sorting a element in the array till j-1
    quickSortActual(arr, j+1, high);// Sorting a element in the array from j+1 till high 
  }
}

void quickSort(int arr[], int size) 
{ 
  quickSortActual(arr, 0, size - 1); //low is 0(first element) and high is size - 1 (last element)
}