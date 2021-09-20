#include<stdio.h>

int main(){
    int x, y,d, n;
    scanf("%d %d", &x, &y);
        
    for ( ; x<=y; x++) {
        for (n=2,d=2; d<x; d++, n++) {
            if (x%d ==0)
                break;                    
        }
        if (n == x) {
            printf("%d ", x);
        }
    }
        
    return 0;
}



//2020.11.11 為什麼只有85分？
#include<stdio.h>
int x,y,i,k,p;
int main(){
    scanf("%d %d",&x,&y);
    if (x<2 && 2<y) printf("2 ");
    for (i=x+1;i<y;i++){
        for(k=2;k<i;k++){
        	if (i%k==0) break;
			if  (k==i-1) printf("%d ",i);

        }
    }

    return 0;
}
