#include <iostream>
#include <queue>
#include <map>
using namespace std;
typedef pair<int,int> P;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m, k, A, B;
    cin >> n >> m >> k;
    cin >> A >> B;
    vector<bool> go(n+1);
    vector<bool> visit(n+1);
    vector <int>  v[n+1]; //i -> vertice, 1=can go, 0=埋伏 
    for(int i=0; i<n+1; i++){
        go[i] = true;
        visit[i] = false;
    }

    for(int i=0; i<m; i++){
        int a, b;
        cin >> a >> b;
        v[a].push_back(b);
    }
    for(int i=0; i<k; i++){
        int x;
        cin >> x;
        go[x] = false;
    }
        
    queue<int> q;
    q.push(A);
    visit[A] = true;

    while(q.size()){
        int p = q.front();
        q.pop();
        visit[p] = true;
        if(p==B){
            break;
        }
        if(!go[p])
            continue;

        //push others into queue - breadth
        for(auto vi : v[p]){
            int nx = vi;
            if(go[vi] && !visit[vi])
                q.push(nx);
        }
    }

    if(visit[B])
        cout << "SAFE" << endl;
    else
        cout << "UNSAFE"  << endl;
    return 0;
}