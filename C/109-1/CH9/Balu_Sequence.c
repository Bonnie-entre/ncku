#include<stdio.h>
long int i;

long int fine(long int x){
	if(x<=2) return 1;
    else return ((2*fine(x-1)+3*fine(x-2)) % 1000000007);
}

int main(){
    scanf("%ld",&i);
    printf("%ld",fine(i));
    return 0;
}

