#include<stdio.h>
char x;
int i;
int main(){
	scanf("%c",&x); 
    for (i=1;i<21;i++){
        switch(x){
        	case 'A': printf("C"); break;
            case 'B': printf("R"); break;
            case 'C': printf("W"); break;
            case 'D': printf("Z"); break;
            case 'E': printf("G"); break;
        }
        scanf("%c",&x);       
    }
        
    return 0;
}

//2020.11.12
#include<stdio.h>
char x;
int i;
int main(){
    
    for (i=0;i<20;i++){
    	scanf("%c",&x);	
    	switch(x){
            case 'A': printf("C"); break;
            case 'B': printf("R"); break;
            case 'C': printf("W"); break;
            case 'D': printf("Z"); break;
            case 'E': printf("G"); break;
        }
    }
    return 0;
}

