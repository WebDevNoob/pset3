/**
 * helpers.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Helper functions for Problem Set 3.
 */
       
#include <cs50.h>
#include <math.h>
#include "helpers.h"

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{
    int low = 0, high = n, mid;
    do{
        mid = floor(((low + high) / 2));
        if(value < values[mid]){
            high = mid - 1;
        }else
        if(value > values[mid]){
            low = mid + 1;    
        }
        }while(value != values[mid] && low <= high);
        if(value == values[mid]){
            return 1;
        }else{
            return 0;
        }
    return 0;
}

/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
    for(int i = 0; i < n; i++){
        for(int j = i + 1; j < n; j++){
            if(values[i] > values[j]){
            
                int swap = values[i];
                values[i] = values[j];
                values[j] = swap;   
            }   
        }
     }
     return;   
}
    

