/* Loader Start */
#include <stdio.h>
#include <stdint.h>
#include <assert.h>
#define swap(x, y) {int tmp = x; x = y; y = tmp;}
int size;

// Function Declairation 
void sort_pointers(int **ptr_arr, int *arr, int size);
void quicksort(int *a, int low, int high, int r[]);
int partition(int *a, int low, int high, int r[]);

// Main Function
int main(){
    // Read length of array
    int N;
    scanf("%d", &N);
    
    // Read entries of array, starting from idx = 0, also store a copy
    int arr[N], backup[N];
    for(int i = 0; i < N; ++i){
        scanf("%d", &arr[i]);
        backup[i] = arr[i];
    }

    // Sort the pointers of arr[] into ptr_arr[]
    int *ptr_arr[N];
    sort_pointers(ptr_arr, arr, N);

    // Check if arr[] is unchanged
    for(int i = 0; i < N; ++i){
        assert(arr[i] == backup[i]);
    }

    // Check if all entry of ptr_arr[] are pointers of arr[] entries
    for(int i = 0; i < N; ++i){
        assert((ptr_arr[i] >= arr) && (ptr_arr[i] < &arr[N]));
    } 

    // Check if value pointed by pointers in ptr_arr[] are in descending order
    for(int i = 0; i < N - 1; ++i){
        assert(*ptr_arr[i] >= *ptr_arr[i + 1]);
    }

    // Check if address of every arr[] entries appears in ptr_arr[]
    uintptr_t a = (uintptr_t)arr, b = (uintptr_t)ptr_arr[0];
    for(int i = 1; i < N; ++i){
        a ^= (uintptr_t)&arr[i];
        b ^= (uintptr_t)ptr_arr[i];
    }
    assert(a == b);

    // Success if program runs until here.
    printf("All test passed successfully! :)\n");
    return 0;
}

void sort_pointers(int **ptr_arr, int *arr, int size)
{
    int index_arr[size];
    for( int i=0; i<size; i++){
        index_arr[i] = i; 
    }
    quicksort(arr, 0, size - 1, index_arr);

    //Debug
    // for(int i=0; i<size; i++) {
    //     printf("%d ", index_arr[i]);
    // }
    // printf("\n");
    //Debug

    for(int i =size-1, k=0; i>=0; i--, k++){
        *(ptr_arr + k) = arr+index_arr[i];
        // printf("%d ", *(arr+index_arr[i]));
    }
    // printf("\n");
}

void quicksort(int *a, int low, int high, int r[]) {
    
    if(low<high)
    {
    	int middle = partition (a, low, high, r);
        quicksort(a, low, middle - 1, r);
        quicksort(a, middle + 1, high, r);   
    }
}

int partition(int *a, int low, int high, int r[]) {
	int pivot = *(a+r[high]);
    int s = low-1;
    for(int i=low; i<high; i++)
    {
        if(*(a+r[i])<=pivot) 
        { 
            s++;
        	swap(r[i], r[s]);  
        }
    }
    s++;
    swap(r[s], r[high]); 

    return s;
}