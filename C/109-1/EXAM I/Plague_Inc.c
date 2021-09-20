#include<stdio.h>

float R,num;
int N,i;

int main(){
    num=1;
    scanf("%f %d",&R,&N);
    for (i=1;i<=N;i++){
    	num*=R;
    }
    num= (int)num;
    printf("%.0f",num);
    return 0;
}
