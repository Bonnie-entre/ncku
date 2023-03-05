#include<stdio.h>
char c;
int x;
#define SPACE ' '

int main(){
    scanf("%c",&c);
    
    while (c!='\n'){
    	for (x=1;c==SPACE;x++) {
            if (x==1) printf(" ");
        	else { 
                scanf("%c",&c);
                if (c == '\n')
                    return 0;
            }
        }
        printf("%c",c);
        scanf("%c",&c);
    }
    return 0;
}

