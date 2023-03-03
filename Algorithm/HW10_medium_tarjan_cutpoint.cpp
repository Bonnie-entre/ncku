#include <iostream>
#include<stdio.h>
#include<cstring>
#include<vector>
#include<algorithm>
#include<set>
#include<map>
#define MAXSIZE 200000
using namespace std;
struct Node
{
    int u,v;
    Node(int x,int y)
    {
        u=x;
        v=y;
    }
   friend bool operator <(Node node1,Node node2)
   {
        if(node1.u==node2.u)
            return node1.v<node2.v;
        else return node1.u<node2.u;
   }
};

vector<int> ans;
vector<int> V_Edge[MAXSIZE];
int dfn[MAXSIZE];  //dfs The traversal order of 
int low[MAXSIZE];  // Corresponding to the minimum subscript that can be traced back to the nodes in the following table 
int visited[MAXSIZE]; // Mark whether you have visited 
int Count=0;        // Label the traversal 
set<int> Ver;
set<Node> Edge;

void tarjan_dfs(int u,int father)
{
    visited[u]=1;
    dfn[u]=low[u]=++Count;  // Initial initialization ,low=dfn  node u The smallest node that can be traced back is itself 
    for(int i=0;i<V_Edge[u].size();i++)
    {
        int v=V_Edge[u][i];
        if(v==father) continue;
        if(visited[v]==0)  // This node has not yet accessed the tree edge 
        {
            tarjan_dfs(v,u);
            low[u]=min(low[u],low[v]);  // Take the minimum value that can be traced back by itself and the tree followed by its child nodes 
            if(low[v]>=dfn[u])  // No ring formed , therefore u For the cut point 
                ans[u]++;
                // Ver.insert(u);
        }
        else                // This node has been accessed , Back to the side 
            low[u]=min(low[u],dfn[v]);  // Take the minimum value of the traversal order of nodes that can be accessed by backtracking and backtracking itself 
        // if(low[v]>=dfn[u]) and if(low[v]>dfn[u]) It's actually OK to put it here , Just put it in tarjan_dfs(v,u) After recursion , But we need to for Inside the loop 
    }
}


struct cmp{
    bool operator() (pair<int,int> &a, pair<int,int> &b)const {
        if(a.first==b.first)
            return a.second < b.second;
        return a.first > b.first;
    }
};

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n,m,v,u;
    cin >> n >> m >> v >> u;
    
    ans = vector<int>(n,1);
    ans[0] = 0;
    while(v!=-1 && u!=-1){
        V_Edge[v].push_back(u);  // Because it's an undirected graph , So an edge should be added to both tables 
        V_Edge[u].push_back(v);
        cin >> v >> u;
    }

    tarjan_dfs(0,-1);
    
    vector<pair<int,int>> answer;
    for(int i=0; i<n; i++)
        answer.emplace_back(pair<int,int>{ans[i],i});

    sort(answer.begin(),answer.end(),cmp());


    for (int i = 0; i < m; ++i) {
        cout << answer[i].second << ' ' << answer[i].first << endl;
    }

    return 0;
}