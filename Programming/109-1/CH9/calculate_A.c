#include<stdio.h>

int m,n;

int calculate_A(int n,int m){
    if (n==0) return(m+1);
    else if (m==0) return calculate_A(n-1,1);
    else return calculate_A(n-1,calculate_A(n,m-1));
}

int main(){
    scanf("%d%d",&n,&m);
    printf("%d",calculate_A(n,m));
    return 0;
}

