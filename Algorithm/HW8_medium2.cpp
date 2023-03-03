#include <iostream>
#include <vector>
#include <cmath>
#include <climits>
using namespace std;

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
 
    int N, x, maxSum=INT_MIN, sum; 
    cin >> N;

    vector <int> in; 
    vector <int> maxR(N);
    vector <int> maxL(N);  
    cin >> x;
    in.push_back(x);
    maxL[0] = sum = x;

    for( int i=1; i<N; i++){
        cin >> x;
        in.push_back(x);
        if(sum < 0)     //key
            sum = 0;
        sum += x;       //key
        maxL[i] = max(sum, maxL[i-1]);
    }

    maxR[N-1] = sum = in[N-1];
    for( int i=N-2; i>=0; i--){
        if(sum < 0)
            sum = 0;
        sum += in[i];
        maxR[i] = max(sum, maxR[i+1]);
    }
    
    for(int i=0; i<N-1; i++)
        maxSum = max(maxSum, maxL[i]+maxR[i+1]);
    
    cout << maxSum << endl;
    return 0;
}