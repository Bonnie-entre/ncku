#include<stdio.h>
#include <stdbool.h>

bool CountR(int r[], int num){
    int count=0;
    for(int i=0; i<num; i++){
        if(r[i]==0) {count++;}
    }
    if(count==1) {return true;}
    return false;
}

bool check( int a[], int r[], int pairs, int num, int count ){
    for(int i=0; i<num-2; i++ ) {
        for (int j=i+1; j<num-1; j++) {
            for (int c=j+1; c<num; c++){

                if(c!=j && r[i]!=1 && r[j]!=1 && r[c]!=1 && ( a[i]+a[j]==a[c] || a[j]+a[c]==a[i] || a[i]+a[c]==a[j] )){
                    r[i] = 1;
                    r[j] = 1;
                    r[c] = 1;
                    count++;
                    
                    if (count == pairs) {  
                        return true; 
                    }
                    
                    //check( a ,r ,pairs ,num , count);
                    if( !check( a ,r ,pairs ,num , count) ) {
                        //printf("Into if(!check)\t\tcount=%d  (%d, %d, %d)  index=%d,%d,%d\n", count, a[i], a[j], a[c], i, j, c);
                        r[i] = 0;
                        r[j] = 0;
                        r[c] = 0;
                        count--;
                    }
                }
            }
        }
    }
    return CountR(r, num);
}

int main () {
    int num;
    int a[50]={0}, r[50]={0};
    scanf("%d", &num);
    for(int i=0; i<num; i++)
    {
    	scanf("%d", &a[i]);
    }

    int pairs = (num-1)/3;
    int count=0;

    if ( check(a,r,pairs, num, count) ){
        for(int i=0; i<num; i++){
            if(r[i]==0) {
                printf("%d", a[i]);
                return 0;
            }
        }
    }
    //else { printf("Fail"); }
    
    return 0;
}