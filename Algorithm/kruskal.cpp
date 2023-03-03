#include <iostream>
#include <vector>
#include <queue>
using namespace std;

//kruskal 模板

struct edge {
    int v1, v2, wei;
    edge(int x, int y, int z) {v1=x,v2=y,wei=z;} 
};
struct cmp {
    bool operator() (const edge *a, const edge *b)const {
        return a->wei < b->wei;
    }
};

int find(vector<int> &pars, int vn) {  //vertic now
    if(pars[vn] == -1)
        return vn;
    return pars[vn] = find(pars, pars[vn]);
}

bool check(vector<int> &pars, int v1, int v2) {
    int root1 = find(pars, v1), root2 = find(pars, v2);
    if(root1 == root2)
        return false;
    pars[root1] = root2;
    return true;
}

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, m, v1, v2, wei;
    cin >> n >> m;
    
    priority_queue<edge*, vector<edge*>, cmp> pq;
    vector<int> pars(n, -1);
    
    for(int i=0; i<m; i++) {
        cin >> v1 >> v2 >> wei;
        pq.emplace(new edge(v1,v2,wei));
    }
    
    int cnt = n-1, total_wei = 0;
    while(cnt) {
        edge *edg = pq.top();
        pq.pop();
        if(check(pars, edg->v1, edg->v2)) {
            total_wei += edg->wei;
            cnt--;
        }
    }

    cout << total_wei;
    return 0;
}