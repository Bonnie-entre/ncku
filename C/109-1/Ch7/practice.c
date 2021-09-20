#include<stdio.h>
long long m,n,ans;
int i,j,k;
int main(){
    scanf("%lld %lld",&m,&n);
    for (ans=1,i=1,j=1,k=1;i<=m && j<=n && k<=m-n;i++,j++,k++)
        ans*=i/j/k;

    printf("%lld",ans);
    return 0;
}
