#include<stdio.h>
int a,b,xa,xb;
int main(){
    scanf("%d %d\n",&a,&b);
    for (;a>0 && b>0;){
        scanf("%d",&xb);
    	b-=xb;
    	if (b<0) {printf("A"); break;}
    	scanf("%d",&xa);
    	a-=xa; 
    	if (a<0) {printf("B"); break;}
    }    	
  
    return 0;
}
