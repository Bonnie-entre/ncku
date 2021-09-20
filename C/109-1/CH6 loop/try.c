#include<stdio.h>
int x,n,T,i,a,b,c,d,e;

int jei(int n) {
    for (T=1,i=1;i<=n;i++) T = T*i;
	return T;
}

int main(){
    scanf("%d",&x);
    printf("%d\n",x);



    printf("%d\n",(jei(a)+jei(b)+jei(c)+jei(d)+jei(e)));
    return 0;
}
//jei(x/10000)+jei(x%10000/1000)+jei(x%1000/100)+jei(x%100/10)+jei(x%10) == x
    if (x/10000>0) a=x/10000;
    else a=0;
    if (x%10000/1000>0) b=x%10000/1000;
    else b=0;
    if (x%1000/100>0) c=x%1000/100;
    else c=0;
    if (x%100/10>0) d=x%100/10;
    else d=0;
    if (x%10>0) e=x%10;
    else e=0;