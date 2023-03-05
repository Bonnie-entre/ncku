#include<stdio.h>
int a[10000],i,k,x1,x2,m;

int series(int a,int b,int c){
	x2=a+b;
    x1=b;
    k++;
    if (k<=c) series(x1,x2,c);
    else {return x2;}
    return 0;
}

int main(){
    for (i=1;m!=1;i+=3)
    	scanf("%d",&a[i]);
        printf("%d %d",i,a[i]);

        if (a[i]==a[i+1] && a[i+1]==a[i+2] && a[i]==0) m=1;
    k=2;
    for (i=1;;i+=3)
        if (a[i]!=0)
        	printf("%d",series(a[i],a[i+1],a[i+2]));
		else return 0;    
    return 0;
}

