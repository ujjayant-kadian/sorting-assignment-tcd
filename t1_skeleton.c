#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "t1.h"


//Fills the array with ascending, consecutive numbers, starting from 0.
void fill_ascending(int *array, int size)
{
    for(int i = 0; i < size; i++){
        array[i] = i;
    }
    
}
//Fills the array with descending numbers, starting from size-1
void fill_descending(int *array, int size)
{
    int j = size - 1;
    for(int i = 0; i < size; i++){
        array[i]=j;
        j--;
    }
}

//Fills the array with uniform numbers.
void fill_uniform(int *array, int size)
{
    srand(time(0));
    int number = rand() % size;
    for (int i = 0; i < size; i++){
        array[i] = number;
    }
    
}

//Fills the array with random numbers within 0 and size-1. Duplicates are allowed.
void fill_with_duplicates(int *array, int size)
{
    srand(time(0));
    int number = 0;
    for(int i = 0; i < size; i++){
        //finding random numbers and inserting them into the array
        number = rand() % size;
        array[i] = number;
    }
    
}


//Fills the array with unique numbers between 0 and size-1 in a shuffled order. Duplicates are not allowed.
void fill_without_duplicates(int *array, int size)
{
    //First filling the array with distinct numbers
    fill_ascending(array, size);
    srand(time(0));
    int j = 0, temp = 0;
    for(int i = 0; i < size; i++){
        //Shuffling the elements in the array
        j = rand() % size;
        temp = array[i];
        array[i] = array[j];
        array[j] = temp;
    }
}

void printArray(int* arr, int size){
  int i;
  for(i=0; i<size;i++){
    printf("%d ", arr[i]);
  }
  printf("\n");
}