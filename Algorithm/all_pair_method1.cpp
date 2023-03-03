#include<iostream>
#include<vector>

using namespace std;

//--- shortest weight use dp bottom up ， slowest

vector<vector<int>> shortest_p_helper(vector<vector<int>> &pre ,vector<vector<int>> &w, int n) {
    vector<vector<int>> ret(n,vector<int>(n,INT32_MAX));

    for(int i=0; i<n; i++) {
        for(int j=0; j<n; j++) {
            for(int mid=0; mid<n; mid++) {
                if(pre[i][mid] != INT32_MAX && w[mid][j] != INT32_MAX)
                    ret[i][j] = min(ret[i][j], pre[i][mid]+w[mid][j]);
            }
        }
    }

    return ret;
}

int main(void) {
    int n,m,v1,v2,wei;
    cin >> n >> m;

    vector<vector<int>> w(n, vector<int>(n,INT32_MAX));
    
    for(;m;m--) {
        cin >> v1 >> v2 >> wei;
        w[v1][v2] = wei;
    }
    for(int i=0; i<n; i++)
        w[i][i] = 0;  //自己到自己為0
    cout << '\n';

    vector<vector<int>> L = w;

    //--- get all pairs , this is O(n^4)

    for(int i=1; i<n-1; i++) {
        L = shortest_p_helper(L, w, n);
        
        for(int i=0; i<n; i++) {
            for(int j=0; j<n; j++)
                cout << L[i][j] << ' ';
            cout << '\n';
        }
        cout << '\n';
    }

    //--- get all pairs , this is O(n^3 * lg(n))
    //for(int i=1; i<n-1; i *=2) {
    //    L = shortest_p_helper(L,L,n);
    //    for(int i=0; i<n; i++) {
    //        for(int j=0; j<n; j++)
    //            cout << L[i][j] << ' ';
    //        cout << '\n';
    //    }
    //    cout << '\n';
    //}

    return 0;
}