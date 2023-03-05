#include<stdio.h>
#include <string.h>
#include <ctype.h>  
#define Max_line 100
#define Max_ch 100

int read_line(char str[][Max_ch], int n, int line);

int main () {
    int num, num_line = 0;
    scanf("%d ", &num);

    char ch;
    char name_str[num][Max_ch], name_cmpstr[num][Max_ch], name[Max_ch], name_org[Max_ch];
    for(;;){
        // input
        if( num_line == Max_line || num_line == num ){ break; }
        int i=0;
        while(( ch = getchar() ) != '\n'){      //這邊應該有更好的 input法
            name[i] = tolower(ch);
            name_org[i] = ch;
            i++;
        }
        name[i] = '\0';
        name_org[i] = '\0';

        // compare
        // 找到插入的位置
        int j, k;
        for( j=0; j<num_line; j++){
            if( strcmp(name, name_str[j]) <0 ){
                break;
            }
        }

        // 往下挪
        for( k=num_line; k>j; k--){
            strcpy(name_str[k], name_str[k-1]);
            strcpy(name_cmpstr[k], name_cmpstr[k-1]);
        }

        // 插入
        strcpy(name_str[j], name);
        strcpy(name_cmpstr[j], name_org);
        num_line++;
        // printf("%s\n", name);       // 為什麼沒有tolower 測資pat後面會有奇怪的符號？

        // renew
        for( int n=0; name[n]!='\0'; n++){
            name[n] = '\0';
            name_org[n] = '\0';
        }
    }

    // output
    for( int i=0;i<num;i++){
        printf("%s\n", name_cmpstr[i]);
    }
    return 0;
}
