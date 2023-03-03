#include <iostream>
#include <vector>
#include <map>
#include <climits>
using namespace std;

int main(){
    int n, m, f;
    cin >> n >> m >> f;

    map<int, long long int> mp[n+1];  //node, dis
    vector<bool> factory(n+1, false);
    for(int i=0;i <m; i++){
        int a, b, w;
        cin >> a >> b >> w;
        mp[a][b] = mp[b][a] = w;
        // mp[a][b] =  w;  //單向
    }
    for(int i=0; i<f; i++){
        int x;
        cin >> x;
        factory[x] = true;
    }

    vector<long long int> ans(n+1, 0);

    for(int j=1; j<=n; j++){
        //Dijkstra Alogorithm - shortest path
        if(factory[j])  //is factory
            continue;

        long long int dis[n+1];
        bool finish[n+1];
        int count = 0, min_index = j;    //start from j
        for(int i=0; i<=n;i++){
            dis[i] = INT_MAX;
            finish[i] = false;
        }
        dis[min_index] = 0;
        while(count<n){
            for(auto m : mp[min_index])
                if(m.second + dis[min_index] < dis[m.first] )
                    dis[m.first] = dis[min_index] + m.second;

            finish[min_index] = true;
            count++;
            
            int min = INT_MAX;
            for(int i=1; i<=n; i++)
                if(!finish[i] && min > dis[i]){
                    min = dis[i];
                    min_index = i;
                }
        }

        int min = INT_MAX;
        for(int i=1; i<=n; i++){
            if(factory[i]){
                min = dis[i] < min ? dis[i] : min;
            }
        }
        // cout << min << endl;
        if(min == INT_MAX)
            ans[j] = -1;
        else
            ans[j] = min;
    }

    for(int i=1; i<ans.size(); i++)
        cout << ans[i] << " ";
    
    return 0;
}