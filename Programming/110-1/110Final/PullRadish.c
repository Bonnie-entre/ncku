#include<stdio.h>
#include<stdlib.h>

int pull_radish(int *l, int *r, int *pos, int x);

int main() {
    int N, y, x;
    scanf("%d %d %d", &N, &y, &x);
    int *farm = malloc(N*sizeof(int));

    // initialize farm[N]
    for(int i=0; i<N; i++) {
        farm[i]=1;
    }

    int total = pull_radish(&farm[0], &farm[N-1], &farm[y], x);
    printf("%d\n", total);
    for(int i=0; i<N; i++) {
        printf("%d ", farm[i]);
    }

    return 0;
}

// l represents the first radish to the left 左邊第一個
// r represents the first radish to the right 右邊第一個
// pos represents Ariel's position
// x represents the interval
int pull_radish(int *l, int *r, int *pos, int x) {
    // 原點 array = l+pos, 由此前後算

    int count = 0;
    for( int i=x; pos-i>=l; i+=x ){
        *(pos-i) = 0;
        count ++;
    }
    for( int i=x; pos+i<=r; i+=x ){
        *(pos+i) = 0;
        count ++;
    }

    return count;
}