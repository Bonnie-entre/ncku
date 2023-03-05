#include<stdio.h>
#include<stdlib.h>
int M,a[10],i,j;
int main(){
    M=0;
    
    for (i=0;i<10;i++)
    	scanf("%d ",&a[i]);
    scanf("\n");
    for(i=0;i<10;i++)
        for(j=0;j<10;j++)
    		if ((a[i]+a[j])*abs(i-j)>M) M=(a[i]+a[j])*abs(i-j);
    printf("%d",M);
    return 0;
}
