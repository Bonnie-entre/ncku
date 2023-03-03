#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
 // the classcal solution - 2 dimansion dp cannot pass due to Segamentation Fault (broke memory)
 // use 1 dimension dp 

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
 
    int N, m; //number, limit of minutes
    cin >> N >> m;
    vector <int> dp(m+1);   

    vector<pair<int, int>> score(N);
    for(int i = 0; i < N; i++){
        int sc, time;
        cin >> sc >> time;
        score[i].first = time;
        score[i].second = sc;
    }   
    sort(score.begin(), score.end());

    for(int i = 0; i < N; i++){
        for(int w = m; w >= score[i].first; w--){
            dp[w] = max(score[i].second + dp[w - score[i].first],
                        dp[w]);
        }
    }
    cout << dp[m];
    return 0;
}