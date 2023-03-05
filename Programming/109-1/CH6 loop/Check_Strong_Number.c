

//20201112
#include<stdio.h>
int n,a,b,c,d,e,x,ans,i,k;
int jei(int x){   
    if (x==0) ans=1;
    else {
        for(i=1,ans=1;i<=x;i++)
    		ans*=i;
    }
    return ans;
}
int main(){
    
    scanf("%d",&n);
    a=n/10000;
    b=n%10000/1000;
    c=n%1000/100;
    d=n%100/10;
    e=n%10;
  
    if (a==0 && b==0 && c==0 && d==0) k= jei(e);
    else if (a==0 && b==0 && c==0) k=jei(d)+jei(e);
    else if (a==0 && b==0) k=jei(c)+jei(d)+jei(e);
    else if (a==0) k=jei(b)+jei(c)+jei(d)+jei(e);
    else k=jei(a)+jei(b)+jei(c)+jei(d)+jei(e);
    
    if (k==n) printf("%d is a strong number.",n);
    else printf("%d is not a strong number.",n);
    return 0;
}