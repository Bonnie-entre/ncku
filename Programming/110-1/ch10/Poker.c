#include <stdio.h>
#include <stdbool.h>
#define NUM 5
// 比較層級，用數字好了～
//考慮同層級，要先比數字，再比花色  //到時候相同再進去array查找

int RankPlayer( char arr[][2] );

int main(void){
    char a[NUM][2];
    char b[NUM][2];
    char c[NUM][2];
    char d[NUM][2];
    for( int i=0; i<NUM; i++){
        for( int j=0; j<2; j++){
        a[i][j] = 0;
        b[i][j] = 0;
        c[i][j] = 0;
        d[i][j] = 0;
        }
    }

    //Input
    
    scanf("%1c%1c %1c%1c %1c%1c %1c%1c %1c%1c", &a[0][0], &a[0][1], &a[1][0], &a[1][1], &a[2][0], &a[2][1], &a[3][0], &a[3][1], &a[4][0], &a[4][1]);
    getchar();
    scanf("%1c%1c %1c%1c %1c%1c %1c%1c %1c%1c", &b[0][0], &b[0][1], &b[1][0], &b[1][1], &b[2][0], &b[2][1], &b[3][0], &b[3][1], &b[4][0], &b[4][1]);
    getchar();
    scanf("%1c%1c %1c%1c %1c%1c %1c%1c %1c%1c", &c[0][0], &c[0][1], &c[1][0], &c[1][1], &c[2][0], &c[2][1], &c[3][0], &c[3][1], &c[4][0], &c[4][1]);
    getchar();
    scanf("%1c%1c %1c%1c %1c%1c %1c%1c %1c%1c", &d[0][0], &d[0][1], &d[1][0], &d[1][1], &d[2][0], &d[2][1], &d[3][0], &d[3][1], &d[4][0], &d[4][1]);
    // getchar();





    // for( int i=0; i<NUM; i++){
    //     printf("%1c%1c ", c[i][0], c[i][1]);
    // }
    // printf("\n");
    // for( int i=0; i<NUM; i++){
    //     printf("%1c%1c ", d[i][0], d[i][1]);
    // }
    // printf("\n");
    return 0;
}

int RankPlayer( char arr[][2] ){
    bool straight = false, flush  = false, four  = false, three  = false;
    int pairs = 0;



}