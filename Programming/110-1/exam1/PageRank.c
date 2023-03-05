#include<stdio.h>

int main () {
    int num;
    scanf("%d ", &num);
    printf("%d\n ", num);

    int a[num][num];
    for(int r=0; r<num; r++)
    {
    	for(int c=0; c<num; c++)
        {
            a[r][c]=0;
        }
    }

    for(int r=0; r<num; r++)
    {
    	for(int c=0; c<num; c++)
        {
            
        	scanf(" %d", &a[r][c]);
            printf("(%d,%d)=%d ", r, c, a[r][c]);
            if (a[r][c]==-1) { c=num; printf("break"); break;}
        }
        printf("\n");
    }
    
    
    return 0;
}

