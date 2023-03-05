#include <stdio.h>
#define SIZE 201

void modify_array(int *);

int main(void) {
    int arr[SIZE];
    for (int i = 0; i < SIZE; i++) {
        scanf("%d", &arr[i]);
    }
    modify_array(&arr[SIZE/2]);
    for (int i = 1; i < SIZE; i++) {
        printf("%d ", arr[i]);
    }
    return 0;
}

void modify_array( int *p ){
    p = p - SIZE/2;    
    int index=0;
    switch ( *p )
    {
    case 1:
        p++;
        while(index<SIZE){
            if(index%2==0){
                *p+=10;
            }
            p++;
            index++;
        }
        break;
    case 2:
        p++;
        while(index<SIZE){
            if(index%3==0){
                *p*=8;
            }
            p++;
            index++;
        }
        break;
    case 3:
        p++;
        while(index<SIZE){
            if(index%5==0){
                *p-=2;
            }
            p++;
            index++;
        }
        break;
    }
    return;
}