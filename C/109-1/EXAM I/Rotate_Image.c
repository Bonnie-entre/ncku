#include<stdio.h>
int degree,m,n,a[100][100],j,i,b[100][100],k;
int main(){
    scanf("%d\n%d %d\n",&degree,&m,&n);
    for (i=0;i<m;i++) {
        
    	for (j=0;j<n;++j)            
            scanf("%d ",&a[i][j]);
        if (j==n-1) scanf("\n");
    }

    for (i=0;i<m;i++) {        
    	for (j=0;j<n;j++)             
            printf("%d ",a[i][j]);
        if (j==n-1) printf("\n");
    }       
    return 0;
}
