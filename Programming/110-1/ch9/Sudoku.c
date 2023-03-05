#include <stdio.h>
#define NUM 9

//是因為 repeat 有可能不只一個數嗎？ yes!!

void check_sudoku(int grid_p[][NUM]);
void checkFunction( int c[], int r[][NUM], int grid_p[][NUM], int row, int column,  int caseNum );

int main(void){
    int grid[NUM][NUM]; // sudoku puzzle
    for(int i = 0; i < NUM; ++i){
        for(int j = 0; j < NUM; ++j){
            scanf("%d", &grid[i][j]);
        }
    }
    check_sudoku(grid);
    return 0;
}

void check_sudoku(int grid_p[][NUM]){
	int check[10]={0}, r[9][9]={0};

    //檢查row
    for(int i=0;i<9;i++)
    {
        int check[10]={0};
    	for(int c=0; c<9; c++)
        {
        	check[ grid_p[i][c] ] ++;
        }

        checkFunction( check, r, grid_p, i, 0, 1 );//function
    }
    
    //檢查column
    for(int c=0; c<9; c++)
    {
        int check[10]={0};
    	for(int i=0;i<9;i++)
        {
        	check[ grid_p[i][c] ] ++;
        }

        checkFunction( check, r, grid_p,0, c, 2 );//function
    }

    //檢查9宮格     
    for(int i=1; i<9; i+=3)
    {
        for(int c=1; c<9; c+=3)
        {
            int check[10]={0};
            check[ grid_p[i][c] ] ++;
            check[ grid_p[i][c-1] ] ++;
            check[ grid_p[i][c+1] ] ++;
            check[ grid_p[i-1][c] ] ++;
            check[ grid_p[i-1][c-1] ] ++;
            check[ grid_p[i-1][c+1] ] ++;
            check[ grid_p[i+1][c] ] ++;
            check[ grid_p[i+1][c-1] ] ++;
            check[ grid_p[i+1][c+1] ] ++;
            checkFunction( check, r, grid_p, i, c, 3 );//function
        }
    }

    //Result
    for(int i=0;i<9;i++)
    {
    	for(int c=0; c<9; c++)
        {
        	if(r[i][c]>0) printf("(%d,%d)\n", i, c);
        }
    }
}

void checkFunction( int c[], int r[][NUM], int grid_p[][NUM], int row, int column, int caseNum ){
    int repeat[10]={0};
    
    int count=0;
	for(int i=0; i<10; i++)
    {
        if(c[i]>1) 
        {
        	repeat[count] = i;
            count++;
        }
    }

    if(repeat[0]==0) return;

    switch(caseNum)
    {
        //row
        case 1: 
            for( int j=0; j<=count; j++ ){
                for (int c=0; c<9; c++)
                {
                    if(grid_p[row][c]==repeat[j]) 
                    {
                        //printf("(%d,%d)\n", row, c);
                        r[row][c]++;
                    }
                }
            }
            
            break;
        //column
        case 2:
            for( int j=0; j<=count; j++ ){
                for (int rr=0; rr<9; rr++)
                {
                    if(grid_p[rr][column]==repeat[j]) 
                    {
                        //printf("(%d,%d)\n", rr, column);
                        r[rr][column]++;
                    }
                }
            }
            break;

        case 3:
            for( int j=0; j<=count; j++ ){
                if(grid_p[row][column]==repeat[j]) //中
                {
                    //printf("(%d,%d)\n", row, column);
                    r[row][column]++;
                }
                if(grid_p[row][column-1]==repeat[j])   //中左
                {
                    //printf("(%d,%d)\n", row, column-1);
                    r[row][column-1]++;
                }
                if(grid_p[row][column+1]==repeat[j])   //中右
                {
                    //printf("(%d,%d)\n", row, column+1);
                    r[row][column+1]++;
                }
                if(grid_p[row-1][column]==repeat[j]) //上中
                {
                    //printf("(%d,%d)\n", row-1, column);
                    r[row-1][column]++;
                }
                if(grid_p[row-1][column-1]==repeat[j]) //上左
                {
                    //printf("(%d,%d)\n", row-1, column-1);
                    r[row-1][column-1]++;
                }
                if(grid_p[row-1][column+1]==repeat[j]) //上右
                {
                    //printf("(%d,%d)\n", row-1, column+1);
                    r[row-1][column+1]++;
                }
                if(grid_p[row+1][column]==repeat[j]) //下中
                {
                    //printf("(%d,%d)\n", row+1, column);
                    r[row+1][column]++;
                }
                if(grid_p[row+1][column-1]==repeat[j]) //下左
                {
                    //printf("(%d,%d)\n", row+1, column-1);
                    r[row+1][column-1]++;
                }
                if(grid_p[row+1][column+1]==repeat[j]) //下右
                {
                    //printf("(%d,%d)\n", row+1, column+1);
                    r[row+1][column+1]++;
                }
            }
            break;
    }   
}