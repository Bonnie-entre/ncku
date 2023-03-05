#include<stdio.h>

int n, i;
char a[1000];
 

int main(){

    scanf("%d\n", &n);
    for (i=0;i<n;i++) scanf("%c", &a[i]);

    for (i=(n-1);i>=0;i--) printf("%c", a[i]);
    
    return 0;
}

