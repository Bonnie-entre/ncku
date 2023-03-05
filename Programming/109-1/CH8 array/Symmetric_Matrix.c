#include<stdio.h>

int n,a[1000][1000],row,col,x;

int main(){
    scanf("%d\n",&n);
    for (row=0;row<n;row++)
        for(col=0;col<n;col++)
            scanf("%d",&a[row][col]);
    	
    
    for (row=0;row<n;row++)
        for(col=0;col<n;col++)
            if (a[row][col] !=a[col][row]) {
                x=0;
    			break;
            }
    		else x=1;
    
    if (x ==1) {
        printf("Yes\n");
    }
    else printf("No\n");
    
    return 0;
}