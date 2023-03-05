#include<stdio.h>

// if 條件寫 a[root]會錯，若輸入數字包含0，即是錯誤狀況
// 且 if 條件中若未設置 root<=n ，a[root]會超出範圍取到亂碼

void Preorder( int a[], int root, int n ){
    if( root<=n ){
        printf("%d ", a[root]);
        Preorder( a, 2*root, n );
        Preorder( a, 2*root+1, n );
    }
}

void Inorder( int a[], int root, int n ){
    if( root<=n ){
        Inorder( a, 2*root, n );
        printf("%d ", a[root] );
        Inorder( a, 2*root+1, n );
    }
}

void Postorder( int a[], int root, int n ){
    if( root<=n ){
        Postorder( a, 2*root, n );
        Postorder( a, 2*root+1, n );
        printf("%d ", a[root]);
    }
}

int main () {
    int s, num;
    int nums[5000]={0};
    scanf("%d %d ", &s, &num);
    if(num==0){
        printf("0");
        return 0;
    }
    for(int i=1; i<=num; i++)
    {
        scanf("%d", &nums[i]);
    }

    switch(s){
        case 0:{   
            Preorder( nums, 1, num );
            break;
        }
        case 1:{
            Inorder( nums, 1, num );
            break;
        }
        case 2:{
            Postorder( nums, 1, num );
            break;
        }  
    }
    return 0;
}