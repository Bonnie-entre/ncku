#include<stdio.h>
#define Max_line 100
#define Max_ch 100

int read_line(char str[][Max_ch], int n, int line);

int main () {
    int num, num_line = 0;
    scanf("%d ", &num);

    char name_str[num][Max_ch];
    for(int i=0;;i++){
        if( num_line == Max_line || num_line == num ){ break; }
        read_line(name_str, Max_ch, i);
        num_line++;
    }


    for( int i=0;i<num;i++){
        printf("%s\n", name_str[i]);
    }
    return 0;
}

int read_line(char str[][Max_ch], int n, int line){
    int ch, i=0;

    while( (ch = getchar() != '\n') ){      //為什麼什麼都沒讀到？？
        if( i<n ){
            printf("into if\n");
            str[line][i++] = ch;
            printf("%c", ch);
        }
    }
    str[line][i] = '\0';
    printf("\n");
    return i;
}