#include<stdio.h>

int i,a[32],b[32],c[32];

int main(){
    
    for (i=0;i<32;i++) 
        scanf("%d\n",&a[i]);
    for (i=0;i<32;i++) 
        scanf("%d",&b[i]);
    for (i=31;i>=0;i--) {
        c[i] = c[i]+a[i]+b[i];
        if (c[i]>=2){
            c[i]=c[i]-2;
            c[i-1]=c[i-1]+1;               
        }                  
    }
    for (i=0;i<32;i++) printf("%d ",c[i]);
   
    return 0;
}

//2020.11.12
#include<stdio.h>
int a[32],b[32],i,c[32];
int main(){
    
    for (i=0;i<32;i++)
        scanf("%d",&a[i]);
    scanf("\n");
    for (i=0;i<32;i++)
        scanf("%d",&b[i]);  
    for (i=31;i>=0;i--){
    	c[i] = a[i]+b[i]+c[i];
        if (c[i]>=2) {c[i]-=2; c[i-1]+=1;}
    }
    for (i=0;i<32;i++) printf("%d ",c[i]);
    
    return 0;
}
