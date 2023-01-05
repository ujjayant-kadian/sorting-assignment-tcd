#include "t1.h"
#include <stdio.h>



int main()
{
    int size = 10;
    int array[size];
    fill_ascending(array, size);
    printArray(array, size);
    fill_descending(array, size);
    printArray(array, size);
    fill_uniform(array, size);
    printArray(array, size);
    fill_with_duplicates(array, size);
    printArray(array, size);
    fill_without_duplicates(array, size);
    printArray(array, size);
    return 0;
}