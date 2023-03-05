#include <stdio.h>
#include <string.h>

int main () {
    char str[1000];
    gets(str);

    int len = strlen(str), i = 0;
    int orig_char, new_char;
    while( (orig_char = getchar()) != '\n' ){
        new_char = orig_char ^ str[i++];
        putchar(new_char);

        if(i==len) i=0;
    }

    return 0;
}