#include<iostream>
#include<vector>
#include<queue>
#include<stack>
using namespace std;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N, M;
    cin >> N;
    while(!cin.eof()){
        cin >> M;
        vector< vector<int> > adjlist(N + 1, vector<int>());
        for(int i = 0; i < M; i++){
            int u, v;
            cin >> u >> v;
            adjlist[u].push_back(v);
        }

        // Line up
        vector<int> inDegree(N + 1, 0);
        for(int v = 1; v <= N; v++)
            for(int i = 0; i < adjlist[v].size(); i++)
                inDegree[adjlist[v][i]] += 1;   //how many path can goto that vertice
                
        priority_queue<int, vector<int>, greater<int> > q;  //from who to start
        for(int i = 1; i <= N; i++)
            if(!inDegree[i])
                q.push(i);

        //
        vector<int> result;
        while(!q.empty()){
            int u = q.top();
            q.pop();
            result.push_back(u);
            for(int i = 0; i < adjlist[u].size(); i++)
                if(--inDegree[adjlist[u][i]] == 0)
                    q.push(adjlist[u][i]);
        }

        //Output
        for(int i = 0; i < result.size(); i++)
            cout << result[i] << " ";
        cout << endl;

        //Next run
        cin >> N;
    }
    return 0;
}