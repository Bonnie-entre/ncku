#include<stdio.h>

int a,b,n,i,ans,pre;

void series(int x1, int x2){
    if (x1==0 && x2==0) {printf("\n"); return;}
    ans = x1+x2;
    pre = x2;
    if (i>n-3) {printf("%d\n",ans); return;}
    i++;  
    series(pre,ans);
    
    return;
}

int main(){
    while (1){
    scanf("%d%d%d",&a,&b,&n);
    i=1;
    
    series(a,b);
    if (!(a+b+n)) break;
    }
    
    
    return 0;
}

