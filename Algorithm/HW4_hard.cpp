#include <iostream>
#include <map>
#include <set>
#include <vector>
using namespace std;

int main(){
    int n, q;
    cin >> n >> q;
    map<int ,set<int> > mp;
    vector< pair<int, int> > v;
    for(int i=0; i<n; i++){
        int x, y;
        cin >> x >> y;
        mp[x].insert(y);
    }
    for(int i=0; i<q; i++){
        int a, b;
        cin >> a >> b;
        v.push_back({a,b});
    }


    for(auto vi : v){
        
    }



    return 0;
}