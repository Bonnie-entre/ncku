#include<stdio.h>
int n;
int main(){
    
    scanf("%d",&n);
    if (n<1) printf("Calm");
    else if (1<=n && n<3) printf("Light air");
    else if (4<=n && n<27) printf("Breeze");
    else if (28<=n && n<47) printf("Gale");
    else if (48<=n && n<63) printf("Storm");
    else  printf("Hurricane");
    
    return 0;
}
