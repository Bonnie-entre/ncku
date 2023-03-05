#include<stdio.h>
int SIZE=100;

void Rotate( int image[][SIZE], int arrayMN[], int times, char dir  );
void VerticleFlip(  int array[][SIZE], int arrayMN[] );
void HorizontalFlip(  int array[][SIZE], int arrayMN[]  );
void Crop(  int array[][SIZE], int arrayMN[], int m, int n , int rStart, int cStart );
void Output(  int array[][SIZE], int arrayMN[]  );


int main () {
    int m, n;
    scanf("%d %d", &m, &n);
    SIZE = m+n;
    int image[m][n];
    int arrayMN[2] = {m,n};
    for(int i=0; i<m; i++){
        for(int j=0; j<n; j++){
            scanf("%d", &image[i][j]);
        }
    }


    int order_num;
    char ord;
    char dir;
    int times;
    scanf("%d", &order_num);
    for( int i=0; i<order_num; i++){    //用這一行，就能逐行讀逐行作，還不需要用array先存起來指令！
        scanf(" %c", &ord);     //統一大家都用前面空格讀掉space~
        switch (ord)
        {
        case 'r':
            // char dir;
            // int times;
            scanf(" %c %d", &dir, &times);

            if(times==0) break;
            Rotate(image, arrayMN, times, dir);
            break;
        
        case 'p':{
            for(int r=0; r<arrayMN[0]; r++){
                for(int c=0; c<arrayMN[1]; c++){
                    printf("%d ", image[r][c]);  
                }
                printf("\n");
            }
            printf("\n");
            break;
        }
        }

    }

    // for(int i=0; i<m; i++){
    //     for(int j=0; j<n; j++){
    //         printf("%d", image[i][j]);
    //     }
    //     printf("\n");
    // }
    return 0;
}

void Rotate( int image[][SIZE], int arrayMN[], int times, char dir ){
    times %= 4;
    if(dir=='l'){         
        times = times * (-1) + 4;   //這數學太聰明了天！  有點像ASCII 轉大小寫！
    }

    int m, n, arrayTemp[SIZE][SIZE];
    for(int r=0; r<SIZE; r++){
        for(int c=0; c<SIZE; c++){
        arrayTemp[r][c] = 0;   
        }
    }

    // for(int i=0; i<times; i++){     //直接統一向右轉90度 多次 
    //     m = arrayMN[1];
    //     n = arrayMN[0];
    //     printf("m=%d n=%d", m, n);
    //     for( int c=0; c<m; c++){
    //         for( int r=n-1, i=0; r>=0; r--, i++ ){
    //             arrayTemp[c][i] = image[r][c];
    //             printf("%d ", image[r][c]);
    //         }
    //         printf("\n");
    //     }
    //     arrayMN[0] = m;
    //     arrayMN[1] = n;
    //     for(int r=0; r<m; r++){
    //         for(int c=0; c<n; c++){
    //             image[r][c] = arrayTemp[r][c];  
    //             printf("%d ", image[r][c]);
    //         }
    //         printf("\n");
    //     }
    // }

    // switch (times)
    // {
    // case 1:
    //     m = arrayMN[1];
    //     n = arrayMN[0];
    //     for( int c=0; c<m; c++){
    //         for( int r=n-1, i=0; r>=0; r--, i++ ){
    //             arrayTemp[c][i] = image[r][c];
    //         }
    //     }
    //     arrayMN[0] = m;
    //     arrayMN[1] = n;
    //     //printf("(m,n)=%d,%d\n", m, n);
    //     for(int r=0; r<m; r++){
    //         for(int c=0; c<n; c++){
    //             image[r][c] = arrayTemp[r][c];  
    //         }
    //     }
    //     break;
    // case 2:
    //     m = arrayMN[0];
    //     n = arrayMN[1];
    //     for( int r=m-1, j=0; r>=0; r--, j++ ){
    //         for( int c=n-1, i=0; c>=0; c--, i++ ){
    //             arrayTemp[j][i] = image[r][c];
    //         }
    //     }
    //     //printf("(m,n)=%d,%d\n", m, n);
    //     for(int r=0; r<m; r++){
    //         for(int c=0; c<n; c++){
    //             image[r][c] = arrayTemp[r][c]; 
    //         }
    //     }
    //     break;
    // case 3:
    //     m = arrayMN[1];
    //     n = arrayMN[0];
    //     for( int c=m-1, i=0; c>=0; c--, i++){
    //         for( int r=0; r<n; r++ ){
    //             arrayTemp[i][r] = image[r][c];
    //         }
    //     }
    //     arrayMN[0] = m;
    //     arrayMN[1] = n;
    //     //printf("(m,n)=%d,%d\n", m, n);
    //     for(int r=0; r<m; r++){
    //         for(int c=0; c<n; c++){
    //             image[r][c] = arrayTemp[r][c]; 
    //         }
    //     }
    //     break;
    // default:
    //     break;
    // }
}
