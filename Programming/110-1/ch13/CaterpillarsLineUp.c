#include<stdio.h>
#include<stdbool.h>
#include <string.h>

void lineup_again(char line[]);
void swap(char *a, char *b);
void reverse_caterpillar(char *l, char *r);

int main() {
    char line[1000000];
    scanf("%s", line);
    lineup_again(line);
    printf("%s", line);
}

void swap(char *a, char *b) {
    char temp;
    temp = *b;
    *b = *a;
    *a = temp;
}

void reverse_caterpillar(char *l, char *r) {
    int stopNum = (r-l)/2; //會是個數！  
    int count = 0;  
    while(count<stopNum+1){
        swap(l++,r--);
        count++;
    }
}

void lineup_again(char line[]) {
    int num = 0, count = 0;
    for( int i=0; i<strlen(line); i++){
        if(line[i]=='A'){
            num++;
        }
        if(line[i]=='Z'){
            num--;
        }
        if(num<0){
            count = 1;
            while(line[++i]!='A'){
                count++;
            }
            reverse_caterpillar(&line[i-count], &line[i]);
            num = 0;
        }
    }
}