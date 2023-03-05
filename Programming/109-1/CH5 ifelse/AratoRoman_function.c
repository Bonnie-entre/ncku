#include<stdio.h>
#define C 'C'
#define M 'M'
#define D 'D'
#define I 'I'
#define V 'V'
#define X 'X'
#define L 'L'

int x,i;
int n,T;


void trans(int x,char a,char b,char c)
    {
        if (x==9) printf("%c%c",a,b);
        else if (x<9 && x>4){
            printf("%c",c);
            for(i=6;i<=x;i++) printf("%c", a);
        }
        else if (x==4) printf("%c%c",a,c);
        else if (x==0) printf("");
        else{
            for(i=1;i<=x;i++) printf("%c",a);        
        }
    }


int main(){
    scanf("%d", &n);
    
    T = n/1000;
    for(i=1;i<=T;i++) printf("M");

    trans((n%1000/100),'C','M','D');
    trans((n%100/10),'X','C','L');
    trans((n%10),'I','X','V');

    return 0;

}