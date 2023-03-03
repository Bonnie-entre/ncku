#include <iostream>
#include <vector>
#include <queue>
using namespace std;


struct Edge {
    long long int v1, v2, w;
    Edge(int x, int y, int z) {v1=x,v2=y,w=z;} 
};

struct cmp {
    bool operator() (const Edge *a, const Edge *b)const {
        return a->w < b->w;
    }
};

int find(vector<int> &v, int vn) {  
    if(v[vn] == -1)
        return vn;
    return v[vn] = find(v, v[vn]);
}

bool check(vector<int> &v, int v1, int v2) {
    int root1 = find(v, v1), root2 = find(v, v2);
    if(root1 == root2)
        return false;
    v[root1] = root2;
    return true;
}

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, m, v1, v2, w;
    cin >> n >> m;
    
    priority_queue<Edge*, vector<Edge*>, cmp> pq;
    vector<int> v(n, -1);
    
    for(int i=0; i<m; i++) {
        cin >> v1 >> v2 >> w;
        pq.push(new Edge(v1,v2,w));
    }
    
    int count = 0;
    long long int Dis = 0;
    while(count < n-1) {
        Edge *edg = pq.top();
        pq.pop();
        if(check(v, edg->v1, edg->v2)) {
            Dis += edg->w;
            count++ ;
        }
    }

    cout << Dis << endl;
    return 0;
}