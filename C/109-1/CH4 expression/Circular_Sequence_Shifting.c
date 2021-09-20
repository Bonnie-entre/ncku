#include<stdio.h>

int main(){
    int n,x,a,b;
    scanf("%d %d %d", &n,&x,&a);

    b = ((x+a)>n ? x+a-n : x+a);
    printf("%d",b);
    printf("%d",(x+a)%n)

    return 0;
}