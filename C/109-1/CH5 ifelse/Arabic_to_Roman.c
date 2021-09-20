#include<stdio.h>

int n, T,H,S,G,i;

int main(){
    scanf("%d", &n);
    
    T = n/1000;
    for(i=1;i<=T;i++) printf("M");
    
    H = n%1000/100;
    if (H==9) printf("CM");
    else if (H<9 && H>5){
        printf("D");
        for(i=6;i<=H;i++) printf("C");
    }
    else if (H==4) printf("CD");
    else if (H==0) printf("");
    else{
        for(i=1;i<=H;i++) printf("C");        
    }

    S = n%100/10;
    if (S==9) printf("XC");
    else if (S<9 && S>5){
        printf("L");
        for(i=6;i<=S;i++) printf("X");
    }
    else if (S==4) printf("XL");
    else if (S==0) printf("");
    else{
        for(i=1;i<=S;i++) printf("X");        
    }

    G = n%10;
    if (G==9) printf("IX");
    else if (G<9 && G>5){
        printf("V");
        for(i=6;i<=G;i++) printf("I");
    }
    else if (G==4) printf("IV");
    else if (G==0) printf("");
    else{
        for(i=1;i<=G;i++) printf("I");        
    }
            
    
    return 0;
}

