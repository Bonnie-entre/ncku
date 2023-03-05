#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// 怎麼用到 union

int * to_binary(void *n){
    int * ans = (int*)malloc(32 * sizeof(int));
    for(int i = 31; i >= 0; --i){
        ans[31-i] = (*(int *)n >> i) & 1;
    }
    return ans;
}

int main () {
    int num_f;
    scanf("%d", &num_f);

    // input
    float * arr_f = malloc( num_f * sizeof(float));
    for( int i=0; i<num_f; i++){
        scanf("%f", &arr_f[i]);
    }

    // float to binary, sum up, print result
    char *result[] = {"Front", "Back"};
    for( int j=0; j<num_f; j++){
        int sum = 0;
        int * arr_a = to_binary( &arr_f[j] );   
        for( int i=0; i<32; i++){
            sum += arr_a[i] * pow(2, 7-i%8);
            // i%8 == 0 -> pow(2,7)     // 7次方 = 7 - i%8
            // i%8 == 1 -> pow(2,6)
            // ...
            // i%8 == 7 -> pow(2,0)

        }
        printf("%s\n",result[sum%2]);
    }
    
    return 0;
}
