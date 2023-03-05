#include <stdio.h>

int main () {
    long long k, ad=2;
    char c, cs;
    scanf("%lld ", &k);

    while(k<0) { k+=26; }
    
    cs = getchar();
    getchar();

    if(cs=='a') ad=1;

    switch(ad)
    {
        case 1:
            do
            {
                c = getchar();
                if (c>='a'&&c<='z')
                {
                    c = (c-'a'+k)%26+'a';
                    k++;
                }
                    
                if ( c>='A' && c<='Z')
                {
                    c = (c-'A'+k)%26+'A';
                    k++;
                }                    
                putchar(c);
            }while(c!='\n');
            
            break;
        case 2:
            do
            {
                k+=26;
                c = getchar();
                if (c>='a'&&c<='z')
                {
                    c = (c-'a'+k)%26+'a';
                    k--;
                } 
                if ( c>='A' && c<='Z')
                {
                    c = (c-'A'+k)%26+'A';
                    k--;
                }   
                putchar(c);
                
            }while(c!='\n');
            
            break;
    }

    
    return 0;
}


