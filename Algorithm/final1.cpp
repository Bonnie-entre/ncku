#include <iostream>
#include <string>
#include <vector>
#include <map>
using namespace std;

long long int Father[2001];

long long int findFather(int x){
    if(Father[x]!=x)
        Father[x] = findFather(Father[x]);
    return Father[x];
}

void Union(long long int x, long long int y){
    x = Father[x];
    y = Father[y];
    if(x<y)
        Father[y] = x;
    else    
        Father[x] = y;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    long long int n, m;
    string s;
    cin >> n >> m;
    vector<string> v;
    // for(int i=0; i<n; i++){
    //     cin >> s;
    //     v.push_back(s);
    // }

    map<long long int, vector< pair<long long int, long long int> >> mp;  //weight, {v1, v2}
    for(long long int i=0; i<m; i++){
        long long int a, b, w;
        cin >> a >> b >> w;
        mp[w].push_back( {a, b} );
    }

    // for(int i=0; i<n; i++)
    //     for(int j=i+1; j<n; j++){
    //         int dif_count = 0;
    //         for(int p=0; p<v[i].size(); p++){
    //             if(v[i][p]!=v[j][p])
    //                 dif_count++;
    //         }
    //         mp[dif_count].push_back({i,j});
    //     }

    //Kruskal's algorithm
    long long int count = 0, Dis = 0;
    for(long long int i=0; i<n; i++)
        Father[i] = i;

    for(auto m = mp.rbegin(); m !=mp.rend(); m++)
        for(auto v : m->second){
            if(count == n -1)
                break;
            if(findFather(v.first) != findFather(v.second)){    //not cycle
                Union(v.first, v.second);
                Dis += m->first;
                count++;
            }
        }

    cout << Dis << endl;
    
    return 0;
}