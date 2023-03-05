#include <stdio.h>
#define M 5
#define N 8
char colors[4] = {'R', 'G', 'B', 'X'};   // Red, Green, Blue, Empty

void spread(char*, int, int);

int main(void) {
    char graph[M][N];
    int row, col;

    for(int i = 0; i < M; i++) {
        for(int j = 0; j < N; j++)
            scanf("%c", &graph[i][j]);
        getchar();      // Ignore '\n'
    }
    scanf("%d %d", &row, &col);    // Starting position
    
    spread(&graph[0][0], row, col);
    
    // Print out the spreading result
    for(int i = 0; i < M; i++) {
        for(int j = 0; j < N; j++)
            printf("%c", graph[i][j]);
        printf("\n");
    }
    return 0;
}

void spread(char *graph, int row, int col) {
    // 每一換行要(M+3)      // why+3??
    int m = M+3;
    // row, col = 4,3 => graph+m*4+2;
    char c = *(graph+m*row+col);

    //上(固定col)
    for( int i=row-1; i>=0 ;i--){
        if( *(graph+m*i+col)==c | *(graph+m*i+col)=='X' ){
            *(graph+m*i+col)=c;
        }
        else{
            i = -1;
        }
    }
    //下
    for( int i=row+1; i<M ;i++){
        if( *(graph+m*i+col)==c | *(graph+m*i+col)=='X' ){
            *(graph+m*i+col)=c;
        }
        else{
            i = M;
        }
    }
    //左
    for( int i=col-1; i>=0 ;i--){
        if( *(graph+m*row+i)==c | *(graph+m*row+i)=='X' ){
            *(graph+m*row+i)=c;
        }
        else{
            i = -1;
        }
    }
    //右
    for( int i=col+1; i<N ;i++){
        if( *(graph+m*row+i)==c | *(graph+m*row+i)=='X' ){
            *(graph+m*row+i)=c;
        }
        else{
            i = N;
        }
    }
}