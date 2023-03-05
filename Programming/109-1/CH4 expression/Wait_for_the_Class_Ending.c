#include<stdio.h>

int main(){
    int H, M;
    scanf("%d %d", &H, &M);
    
    if ((M+50)>60){
    	M = M-10;
        H = H+1;
    }
    else if ((M+50)==60){
        M = 00;
        H = H+1;
    }
    else{
    	M = M+50;  
    }
    
    printf("%02d:%02d\n",H,M);
    
    return 0;
}


//1111
#include<stdio.h>
int hour,min;
int main(){
    scanf("%d %d",&hour,&min);
    
    if (min>=10) {
        hour+=1; 
        min+=50-60;
    }
    else min+=50;
        
    printf("%02d:%02d\n",hour,min);
    return 0;
}


