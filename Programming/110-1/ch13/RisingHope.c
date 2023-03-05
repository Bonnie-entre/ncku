#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int rising_hope(char *R);

int main(int argc, char *argv[])
{
    char in[1005];

    scanf("%s", in);
    int hope = rising_hope(in);
    printf("%d\n", hope);

    return 0;
}

int rising_hope(char *R){
    int ans = 0;
    for(; *R != '\0'; R++ ){
        if( *R=='P'){
            ans++;
        }
        if( *R=='N' ){
            ans--;
        }
    }

    return ans;
}