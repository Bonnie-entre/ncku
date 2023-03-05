#include<stdio.h>
#include<string.h>
#include<stdlib.h>

void add(char a[], char b[], char res[]);

int main(){
    char a[100], b[100], res[105];
    scanf("%s %s", a, b);
    add(a, b, res);
    printf("%s", res);
    return 0;
}

void add(char a[], char b[], char res[]) {
    int digit_a = strlen(a);
    int digit_b = strlen(b);

    // add
    int c = 0, ans = 0, i = 0; //c:進位
    char temp[105] = {'\0'};
    while(digit_a >0 || digit_b>0){
        --digit_a;
        --digit_b;
        ans = 0;
        if(digit_a>=0 && digit_b<0){
            ans = a[digit_a]-'0' + c;
        }
        else if(digit_a<0 && digit_b>=0){
            ans = b[digit_b]-'0' + c;
        }
        else{
            ans = a[digit_a]-'0' + b[digit_b]-'0' + c;
        }

        c = ans / 10;
        temp[i++] = ans%10 + '0';
    }

    // reverse temp, get result
    int j = 0;
    for(int k=i-1; k>=0; k--){
        res[j++] = temp[k];
    }
    res[j]='\0';    //記得！

}