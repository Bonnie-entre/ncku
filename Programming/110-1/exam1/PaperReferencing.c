#include<stdio.h>

int main () {
    int num;
    scanf("%d ", &num);
    int a[num+1][num+1];
    for(int p=0; p<=num; p++)
    {
        for(int q=0; q<=num; q++)
        {
            a[p][q]=0;
        }
    }
    

    int i,  column;
    for(int k=1; k<=num; k++)
    {
        //printf("\ninto forLoop %d\n", k);
        //a[k][k]++;
        scanf("%d", &i);
        if (i==0){ break;}
        
        do
        {
            scanf(" %d", &column);
            //printf("into doLoop:%d column=%d\n", i, column);
            a[i][column]++;
        }while(getchar()!='\n');
    }

    for(int r=1; r<=num; r++)
    {
        for(int c=1; c<=num; c++)
        {
            if(a[r][c]>0) 
            {
                for(int p=1; p<=num; p++)
                {
                    if(a[p][r]>0) { a[p][c]++; }
                }
            }
        }
    }

    for(int p=1; p<=num; p++)
    {
        printf("%d -> ", p);
        for(int q=1; q<=num; q++)
        {
            if(a[p][q]>0) { printf("%d ", q); }
            if(p==q) { printf( "%d ", q ); }
        }
        printf("\n");
    }

    //Debug
    for(int p=0; p<=num; p++)
    {
        for(int q=0; q<=num; q++)
        {
            printf("%d " ,a[p][q]);
        }
        printf("\n");
    }
    
    return 0;
}

