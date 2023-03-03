#include <iostream>
#include <string>
#include <vector>
#include <map>
using namespace std;

int Father[2001];

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
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    string s;
    cin >> n;
    vector<string> v;
    for(int i=0; i<n; i++){
        cin >> s;
        v.push_back(s);
    }

    map<int, vector< pair<int, int> >> mp;  //weight, {v1, v2}
    for(int i=0; i<n; i++)
        for(int j=i+1; j<n; j++){
            int dif_count = 0;
            for(int p=0; p<v[i].size(); p++){
                if(v[i][p]!=v[j][p])
                    dif_count++;
            }
            mp[dif_count].push_back({i,j});
        }

    //Kruskal's algorithm
    int count = 0, Dis = 0;
    for(int i=0; i<n; i++)
        Father[i] = i;

    for(auto m : mp)
        for(auto v : m.second){
            if(count == n -1)
                break;
            if(findFather(v.first) != findFather(v.second)){    //not cycle
                Union(v.first, v.second);
                Dis += m.first;
                count++;
            }
        }

    cout << "The highest possible quality is 1/" << Dis << "." << endl;
    
    return 0;
}