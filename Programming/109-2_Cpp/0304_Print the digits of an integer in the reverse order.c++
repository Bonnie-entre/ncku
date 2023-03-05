#include <stdio.h>
void recall(int);
int n, ans;


int main() {
  
  scanf("%d",&n);  
  recall(n);
  return 0;
}

void recall(int n){
    ans = n %10;
    n = n/10;
    printf("%d",ans);
    if (n>0){
      recall(n);
    }  
}


