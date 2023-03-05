#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<string.h>

// 把 16位元 to int
// int -> binary

int hex_to( char c){
    if(c>=0+'0' && c<=9+'0'){
        return c-'0';
    }
    else if( c=='a'){
        return 10;
    }
    else if( c=='b'){
        return 11;
    }
    else if( c=='c'){
        return 12;
    }
    else if( c=='d'){
        return 13;
    }
    else if( c=='e'){
        return 14;
    }
    else if( c=='f'){
        return 15;
    }
    return 0;
}

// 相干的處理, 不相干的補零（你不會最後一章，那就用蠢方法～



int * to_binary(int n_a, int n_b, int n_c, int n_d, int n_e, int n_f, int n_g, int n_h){
    int * ans = (int*)malloc(8 * 8 * sizeof(int));
    int mod = 0, c =0;
    for(int i = 63; i >= 56; --i){
        ans[i] = n_h%2;
        n_h/=2;
    }
    for(int i = 55; i >= 48; --i){
        ans[i] = n_g%2;
        n_g/=2;
    }
    for(int i = 47; i >= 40; --i){
        ans[i] = n_f%2;
        n_f/=2;
    }

    for(int i = 39; i >= 32; --i){
        ans[i] = n_e%2;
        n_e/=2;
    }
    for(int i = 31; i >= 24; --i){
        ans[i] = n_d%2;
        n_d/=2;
    }
    for(int i = 23; i >= 16; --i){
        ans[i] = n_c%2;
        n_c/=2;
    }
    for(int i = 15; i >= 8; --i){
        ans[i] = n_b%2;
        n_b/=2;
    }
    for(int i = 7; i >= 0; --i){
        ans[i] = n_a%2;
        n_a/=2;
    }
    return ans;
}

void DealBinary( int a[], int n){
    for( int i=0; i<64; ){
        if(i>=64-n-8 && i< 64-n){
            printf("%d", a[i]);
        }
        else{
            printf("0");
        }
        i++;
        if(i%8==0) printf(" ");
    }
    printf("\n");
}

int main () {
    int line;
    scanf("%d", &line);

    for( int j=0; j<line; j++){
        int n, i=0;
        int n1, n2, n3, n4, n5, n6, n7, n8;
        scanf("%d-0x", &n);

        char str[17], ch;
        gets(str);


        if( strlen(str)==16 ){
            n1 = hex_to(str[0])*16 + hex_to(str[1]); 
            n2 = hex_to(str[2])*16 + hex_to(str[3]); 
            n3 = hex_to(str[4])*16 + hex_to(str[5]); 
            n4 = hex_to(str[6])*16 + hex_to(str[7]); 
            n5 = hex_to(str[8])*16 + hex_to(str[9]); 
            n6 = hex_to(str[10])*16 + hex_to(str[11]); 
            n7 = hex_to(str[12])*16 + hex_to(str[13]); 
            n8 = hex_to(str[14])*16 + hex_to(str[15]); 
            int * arr_a = to_binary(n1, n2, n3, n4, n5, n6, n7, n8);

            DealBinary(arr_a, n);
            
        }
        else{
            n1 = hex_to(str[0]); 
            n2 = hex_to(str[1])*16 + hex_to(str[2]); 
            n3 = hex_to(str[3])*16 + hex_to(str[4]); 
            n4 = hex_to(str[5])*16 + hex_to(str[6]); 
            n5 = hex_to(str[7])*16 + hex_to(str[8]); 
            n6 = hex_to(str[9])*16 + hex_to(str[10]); 
            n7 = hex_to(str[11])*16 + hex_to(str[12]); 
            n8 = hex_to(str[13])*16 + hex_to(str[14]); 
            int * arr_a = to_binary(n1, n2, n3, n4, n5, n6, n7, n8);

            DealBinary(arr_a, n);
        }
    }


    return 0;
}



