#include<stdio.h>
int m,n,a[10000],b[10000],i,c[10000],k,j,x;
int main(){
    scanf("%d %d\n",&m,&n);
    for (i=0;i<m;i++) {scanf("%d",&a[i]);}
    scanf("\n");
    for (i=0;i<n;i++) {
        scanf("%d",&b[i]);
    }

    for (i=0;i<m;i++) {
        c[(a[i])]=a[i];}
    for (i=0;i<n;i++) {
        c[(b[i])]=b[i];}

    for (i=0;i<m+n;i++)  printf("%d ",c[i]);
    printf("\n");

    for (i=0;i<100;i++) 
        if (c[i]==0);
        else  printf("%d ",c[i]);
                   
    return 0;
}
