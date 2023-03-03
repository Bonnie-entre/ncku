#include <iostream>
#include <algorithm>
#include <vector>
#include <math.h>
#include <climits>

using namespace std;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int N;
    cin >> N;
    vector<int> p(N);
    for(int i = 0; i < N; i++)
        cin >> p[i];
    vector<vector<int>> s(N - 2, vector<int>(N - 2, 0));
    vector<vector<int>> m(N - 1, vector<int>(N - 1, INT_MAX));
    // initialize m
    for(int i = 0; i < N - 1; i++)
        m[i][i] = 0;
    // initialize s
    for(int i = 0; i < N - 2; i++)
        s[i][i] = i + 1;
    // m[i][j] = min(m[i][k] + m[k + 1][j] + p[i - 1]p[k]p[j])
    for(int l = 2; l <= N; l++){
        for(int i = 1; i < N - l + 1; i++){
            int j = i + l - 1;
            for(int k = i; k < j; k++){
                int q = m[i - 1][k - 1] + m[k][j - 1] + p[i - 1] * p[k] * p[j];
                if(q < m[i - 1][j - 1]){
                    m[i - 1][j - 1] = q;
                    s[i - 1][j - 2] = k;
                }
            }
        }
    }
    cout << m[0][N - 2] << endl;
    return 0;
}