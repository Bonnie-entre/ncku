#include <iostream>
#include <vector>
#include <map>
#include <climits>
using namespace std;

int main(){
    int n, m;
    cin >> n >> m;

    map<int, int> mp[n+1];  //node, dis
    for(int i=0;i <m; i++){
        int a, b, w;
        cin >> a >> b >> w;
        // mp[a][b] = mp[b][a] = w;
        mp[a][b] =  w;  //單向
    }

    //Dijkstra Alogorithm - shortest path
    int dis[n+1];
    bool finish[n+1];
    int count = 0, min_index = 1;    //start from 1
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

    int max = INT_MIN;
    for(int i=2; i<=n; i++){
        max = dis[i] > max ? dis[i] : max;
        cout << dis[i] << endl;
    }
    cout << max << endl;
    
    return 0;
}