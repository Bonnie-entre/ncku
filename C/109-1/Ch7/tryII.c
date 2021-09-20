#include<stdio.h>
char c;
int k;

int main(){
    scanf("%d\n%c",&k,&c);
   
    while (c!='\n'){
        if (k>0 && (c>='A'&&c<='Z')) {
            if (c+k>'Z') printf("%c",'A'+(k-('Z'-c+1))%26);
            else printf("%c",k+c);
        }
        else if (k>0 && (c>='a'&&c<='z')) {
            if (c+k>'z') printf("%c",'a'+(k-('z'-c+1))%26);
            else printf("%c",k+c);
        }
        else if (k<0 && (c>='A'&&c<='Z')) {
            if (c+k<'A') printf("%c",'Z'-(-k-(c-'A'+1))%26);
            else printf("%c",c+k);
        }
        else if (k<0 && (c>='a'&&c<='z')) {
            if (c+k<'a') printf("%c",'z'-(-k-(c-'a'+1))%26);
            else printf("%c",c+k);
        }
        else printf("%c",c);
       
        scanf("%c",&c);   
    }
   
    return 0;
}



