#include <iostream>
#include <vector>
using namespace std;

struct Max {
    int start;
    int end;
    int sum;
};

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
 
    int N, x, startSum=1; 
    cin >> N;
    if(N==1){
        cin >> x;
        cout << x << " " << 1 << " " << 1 << endl;
        return 0;
    }

    vector <int> dp(N);   
    struct Max m = {1,0,0};
    dp[0] = 0;
    for( int i=1; i<=N; i++){
        cin >> x;
        if((dp[i-1]+x) >= x){
            dp[i] = dp[i-1]+x;
            if(m.sum < dp[i]){
                m.end = i;
                m.sum = dp[i];
                m.start = startSum;
            }
        }
        else{
            dp[i] = x;
            if(m.sum < dp[i]){
                m.end = i;
                m.sum = dp[i];
                m.start = i;
            }
            startSum = i;
        }
    }

    cout << m.sum << " " << m.start << " " << m.end << endl;
    return 0;
}