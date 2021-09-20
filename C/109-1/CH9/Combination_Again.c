#include<stdio.h>
int n,m;

int calcu(int x, int y){
    if (y==0||y==x) return 1;
    else return (calcu(x-1,y-1)+calcu(x-1,y));
}


int main(){
	scanf("%d%d",&n,&m);
    printf("%d",calcu(n,m));
    

    return 0;
}

