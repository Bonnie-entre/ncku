#include<stdio.h>
#include<stdlib.h>

int a1,a2,a3,sum,x;

int main(){
    scanf("%d %d %d",&a1,&a2,&a3);
    sum = (a2/100000+a2%10000/1000+a2%100/10+a3/10000+a3%1000/100+a3%10)*3+(a1+a2%100000/10000+a2%1000/100+a2%10+a3%10000/1000+a3%100/10);
    x = abs(10-sum%10);
    if (x==10) x=0;
    printf("%d",x); 
    return 0;
}