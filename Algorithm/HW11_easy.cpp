// Leetcode 1584. Min Cost to Connect All Points
#include <iostream>
#include <vector>
#include <map>
using namespace std;

int Father[1001];

int findFather(int x){
    if(Father[x]!=x)
        Father[x] = findFather(Father[x]);
    return Father[x];
}

void Union(int x, int y){
    x = Father[x];
    y = Father[y];
    if(x<y)
        Father[y] = x;
    else    
        Father[x] = y;
}


int main(){
    int n, x, y;
    cin >> n;

    vector<pair<int, int>> ve;
    for(int i=0; i<n; i++){
        cin >> x >> y;
        ve.push_back({x,y});
    }

    map< int, vector< pair<int, int> > > edges;
    for(int i=0; i<n; i++)
        for(int j=i+1; j<n; j++){
            int dis = abs(ve[i].first - ve[j].first) + abs(ve[i].second - ve[j].second);
            edges[dis].push_back({i,j});    //vertice num is its index in vector ve
        }

    //Kruskal's algorithm
    int count = 0, Dis = 0;
    bool connect[n] = {false};
    for(int i=0; i<n; i++)
        Father[i] = i;

    for(auto e: edges)
        for(auto v : e.second){
            if(count==n-1)
                break;
            if(findFather(v.first) != findFather(v.second)){    //not cycle
                Union(v.first, v.second);
                Dis += e.first;
                count++;
            }
            
        }

    cout << Dis << endl;
    return 0;
}

// 4
// 2 -3 
// -17 -8
// 13 8
// -17 -15