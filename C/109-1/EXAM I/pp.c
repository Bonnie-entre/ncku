#include<stdio.h>
int m,n,a[10000],b[10000],i,j,x,s;
int main(){
    scanf("%d %d\n",&m,&n);
    for (i=0;i<m;i++) {scanf("%d",&a[i]);}
    scanf("\n");
    for (i=0;i<n;i++) {
        scanf("%d",&b[i]);
        if (i==n-1) scanf("\n");}

    
    x=0;
    for (i=0;i<m;i++) 
        if (a[0]<a[i]) x++;
    for (j=0;j<n;j++)
        if (a[0]<b[j]) x++;
    if (x==n+m-1) printf("%d ",a[0]);
    

    





                    
    return 0;
}
