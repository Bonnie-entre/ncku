#include<stdio.h>
#include <math.h>

int main(){
    float s, x, y, z;
    
    scanf("%f %f %f", &x, &y, &z);
    s = (x+y+z)/2, s = s*(s-x)*(s-y)*(s-z);
    
    printf("%.2f", sqrt(s));
    return 0;
}