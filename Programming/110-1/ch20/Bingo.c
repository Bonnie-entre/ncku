#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#define SIZE 8

int * to_binary(void *n){
    int * ans = (int*)malloc(32 * sizeof(int));
    for(int i = 31; i >= 0; --i){
        ans[31-i] = (*(int *)n >> i) & 1;
    }
    return ans;
}

int main(){
    int in[SIZE];
    for( int i=0; i<SIZE; i++){
        scanf("%d", &in[i]);
    }

    // make matrix
    int matrix[SIZE][SIZE];
    

    return 0;
}