#include <stdio.h>
#define N 500
#define swap(x, y) {int tmp = x; x = y; y = tmp;}

// 注意output細節 -- 空白

void quicksort(int a[], int low, int high);
int partition(int a[], int low, int high);

int count=0;
int size;

int main(void)
{
    int array[N];
    scanf("%d", &size);

    for (int i = 0; i < size; i++)
    {
        scanf("%d", &array[i]);
    }

    quicksort(array, 0, size - 1);

    for (int i = 0; i < size; i++)
    {
        printf("%d ", array[i]);
    }
    return 0;
}

void quicksort(int a[], int low, int high) {
    if(low<high)
    {
    	int middle = partition (a, low, high);
        
        for(int i=0; i<size; i++)
        {
            if(i==low) { printf("[ "); }
            if(i==middle) { printf("*"); }
            printf("%d ", a[i]);
            if(i==high) { printf("] "); }
        }
        printf("\n");
        quicksort(a, low, middle - 1);
        quicksort(a, middle + 1, high);   
    }
}

int partition(int a[], int low, int high) {
	int pivot = a[high];
    int s = low-1;
    for(int i=low; i<high; i++)
    {
        if(a[i]<=pivot) 
        { 
            s++;
        	swap(a[i], a[s]);  	//記得＆!! 為麼不用？
        }
    }
    s++;
    swap(a[s], a[high]); 

    return s;
}