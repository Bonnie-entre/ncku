#include<stdio.h>
int n,move,a,new;
int main(){
    scanf("%d %d %d",&n,&move,&a);
    if (move+a>n) 
        new= (move-n+a)%n;
    else new= a+move;

    if (new==0) new=n;
    printf("%d",new);
    return 0;
}
