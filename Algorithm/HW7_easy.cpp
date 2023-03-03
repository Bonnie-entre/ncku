#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n, x, sum=0;
    cin >> n ;

    vector<bool> dp(500*n+1, false);    //500 is the limit of problem setting
    dp[0]= true;
    for(int i=0; i < n; i++){   //list all probability sum
        cin >> x;
        sum += x;
        for(int j=n*500;j>=0;j--){
           if(dp[j]){
               dp[j+x] = true;
           }
        }
    }

    int k = sum/2;      //half can lead to the smallest substract
    while (true){
        if(dp[k]){
            cout<< sum-2*k;     // A=sum-k, B=k
            break;
        }
        k--;
    }

    return 0;
}