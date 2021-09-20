#include<stdio.h>
int n,i,j,k;

int main(){
    scanf("%d",&n);
    for (i=n-1;i>=0;i--){
        for(j=1;j<=i;j++) printf(" ");
    	for(k=1;k<=(2*n-1)-2*i;k++) printf("*");
        printf("\n");
    }
    return 0;
}