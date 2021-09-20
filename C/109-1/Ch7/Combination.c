#include<stdio.h>
#define int long long
int m,n,i,i2,x1,x2;

signed main(){
    scanf("%lld %lld",&m,&n);
    for (i2=1,x1=1,i=m;i>n && i2<=m-n;i2++,i--) x1=x1*i/i2;
    printf("%lld",x1);
    return 0;
}
