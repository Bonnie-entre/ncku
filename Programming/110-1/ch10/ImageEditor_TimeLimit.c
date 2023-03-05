#include<stdio.h>

int SIZE=100;
void Rotate( int array[][SIZE], int arrayMN[], int times );
void VerticleFlip(  int array[][SIZE], int arrayMN[] );
void HorizontalFlip(  int array[][SIZE], int arrayMN[]  );
void Crop(  int array[][SIZE], int arrayMN[], int m, int n , int rStart, int cStart );
void Output(  int array[][SIZE], int arrayMN[]  );

int main () {
    int  m, n, moveNum, moveCount=0;
    int arrayMN[2]={0};
    char ch;
    scanf("%d %d", &m, &n);
    arrayMN[0]=m;
    arrayMN[1]=n;
    // SIZE=n;
    int image[SIZE][SIZE];
    for(int r=0; r<m; r++){
        for(int c=0; c<n; c++){
            scanf("%d", &image[r][c]);
        }
    }

    // Scanf All the Move into Array
    scanf("%d", &moveNum);
    char moveArray[moveNum+1][2];
    int intMoveArray[moveNum+1][5];
    while( moveCount!=moveNum+1 ){
        while ( (ch=getchar()) != '\n'){
            moveArray[moveCount][0] = ch;       // get move char
            if(moveArray[moveCount][0] == 'r'){     // rotate
                scanf("%s %d", &moveArray[moveCount][1], &intMoveArray[moveCount][2]);
            }
            if(moveArray[moveCount][0] == 'c'){     // crop
                scanf("%d %d %d %d", &intMoveArray[moveCount][1], &intMoveArray[moveCount][2], &intMoveArray[moveCount][3], &intMoveArray[moveCount][4]);
            }
        }
        moveCount++;
    }

    // Do Function
    int times=0;
    for(int i=1; i<=moveNum; i++){
        //printf("a=%c\n", moveArray[i][0]);
        switch (moveArray[i][0])
        {
        case 'r':{
            times = intMoveArray[i][2]%4;
            char direction = moveArray[i][1];
            if(times==0) { break; }     //記得加output
            if(direction=='r'){         //Rotate 以右旋轉為主，且L1=R3, L2=R2, L3=R1
                Rotate(image, arrayMN, times);
            }
            else{
                if(times==1) { Rotate(image, arrayMN, 3); }
                else if(times==3) { Rotate(image, arrayMN, 1);}
                else { Rotate(image, arrayMN, times); }
            }
            break;
        }
        case 'v':{
            VerticleFlip(image, arrayMN);
            break;
        }
        case 'h':{
            HorizontalFlip(image, arrayMN);
            break;
        }
        case 'p':{
            Output(image, arrayMN);
            break;
        }
        case 'c':{
            //LRUD //1234 1244
            // printf("--- Into Crop ---\n");

            int m2 = intMoveArray[i][4]-intMoveArray[i][3]+1;   
            int n2 = intMoveArray[i][2]-intMoveArray[i][1]+1;   
            Crop(  image, arrayMN, m2, n2 , intMoveArray[i][3], intMoveArray[i][1] );
            break;
        }
        }
    }
    return 0;
}

void VerticleFlip(  int array[][SIZE], int arrayMN[] ){
    int arrayTemp[arrayMN[0]][arrayMN[1]];
    for( int r=arrayMN[0]-1, j=0; r>=0; r--, j++ ){
        for( int c=0; c<arrayMN[1]; c++ ){
            arrayTemp[j][c] = array[r][c];
        }
    }
    for(int r=0; r<arrayMN[0]; r++){
        for(int c=0; c<arrayMN[1]; c++){
            array[r][c] = arrayTemp[r][c]; 
        }
    }
}

void HorizontalFlip(  int array[][SIZE], int arrayMN[]  ){
    int arrayTemp[arrayMN[0]][arrayMN[1]];
    for( int r=0; r<arrayMN[0]; r++ ){
        for( int c=arrayMN[1]-1, j=0; c>=0; c--, j++ ){
            arrayTemp[r][j] = array[r][c];
        }
    }
    for(int r=0; r<arrayMN[0]; r++){
        for(int c=0; c<arrayMN[1]; c++){
            array[r][c] = arrayTemp[r][c]; 
        }
    }
}

void Crop(  int array[][SIZE], int arrayMN[], int m, int n , int rStart, int cStart ){
    for(int r=rStart-1, j=0; r<rStart+m-1; r++, j++){
        for( int c=cStart-1, k=0; c<cStart+n-1; c++, k++){   
            array[j][k] = array[r][c];
        }
    }

    arrayMN[0]= m;
    arrayMN[1]= n;
}

void Output( int array[][SIZE], int arrayMN[] ){
    for(int r=0; r<arrayMN[0]; r++){
                for(int c=0; c<arrayMN[1]; c++){
                    printf("%d ", array[r][c]);  
                }
                printf("\n");
            }
            printf("\n");
}

void Rotate( int array[][SIZE], int arrayMN[], int times  ){
    int m=SIZE, n=SIZE, arrayTemp[m][n];
    for(int r=0; r<m; r++){
        for(int c=0; c<n; c++){
        arrayTemp[r][c] = 0;   
        }
    }

    switch (times)
    {
    case 1:
        m = arrayMN[1];
        n = arrayMN[0];
        for( int c=0; c<m; c++){
            for( int r=n-1, i=0; r>=0; r--, i++ ){
                arrayTemp[c][i] = array[r][c];
            }
        }
        arrayMN[0] = m;
        arrayMN[1] = n;
        //printf("(m,n)=%d,%d\n", m, n);
        for(int r=0; r<m; r++){
            for(int c=0; c<n; c++){
                array[r][c] = arrayTemp[r][c];  
            }
        }
        break;
    case 2:
        m = arrayMN[0];
        n = arrayMN[1];
        for( int r=m-1, j=0; r>=0; r--, j++ ){
            for( int c=n-1, i=0; c>=0; c--, i++ ){
                arrayTemp[j][i] = array[r][c];
            }
        }
        //printf("(m,n)=%d,%d\n", m, n);
        for(int r=0; r<m; r++){
            for(int c=0; c<n; c++){
                array[r][c] = arrayTemp[r][c]; 
            }
        }
        break;
    case 3:
        m = arrayMN[1];
        n = arrayMN[0];
        for( int c=m-1, i=0; c>=0; c--, i++){
            for( int r=0; r<n; r++ ){
                arrayTemp[i][r] = array[r][c];
            }
        }
        arrayMN[0] = m;
        arrayMN[1] = n;
        //printf("(m,n)=%d,%d\n", m, n);
        for(int r=0; r<m; r++){
            for(int c=0; c<n; c++){
                array[r][c] = arrayTemp[r][c]; 
            }
        }
        break;
    default:
        break;
    }
}
