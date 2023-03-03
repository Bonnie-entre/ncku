#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

struct cmp{
    bool operator() (pair<int,int> &a, pair<int,int> &b)const {
        if(a.first==b.first)
            return a.second < b.second;
        return a.first > b.first;
    }
};
vector<vector<int>> adj;
vector<int> ans;
int *dfn;
int *low;
int T;

stack<int> stacks;
bool *instack;

//int *component; //每個點對應到的 強連通元件收縮成的點
int C;

void DFS(int now){
    dfn[now] = low[now] = ++ T;
    stacks.push(now);
    instack[now] = true;

    for(int i = 0; i < adj[now].size(); i ++){

        if(!dfn[adj[now][i]])
        {
            DFS(adj[now][i]);
            low[now] = min(low[now], low[adj[now][i]]);
            if(low[adj[now][i]] >= dfn[now])
                ans[now]++;
        }
        else if(instack[adj[now][i]])
            low[now] = min(low[now], dfn[adj[now][i]]);
    }
    if(dfn[now] == low[now]){
        int t;
        C ++;
        do
        {
            t = stacks.top(); stacks.pop();
            instack[t] = false;
            //component[t] = C;
        }while(t != now);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n,m,u,v;
    cin>>n>>m;

    adj= vector<vector<int>>(n,vector<int>{});
    dfn=new int [n];
    low=new int [n];
    instack=new bool [n];
    //component=new int [n];
    ans = vector<int>(n,1);
    while (true){
        cin>>u>>v;
        if(u==-1&&v==-1)
            break;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }

    for(int i = 0; i < n; i ++)
    {
        dfn[i] = 0;
        instack[i] = false;
    }
    while(!stacks.empty()) stacks.pop();
    T = 0;
    C = 0;
    ans[0]=0;
    for(int i = 0; i < n; i ++)
    {
        if(!dfn[i])
            DFS(i);
    }


    vector<pair<int,int>> answer;
    for(int i=0; i<n; i++)
        answer.emplace_back(pair<int,int>{ans[i],i});

    sort(answer.begin(),answer.end(),cmp());


    for (int i = 0; i < m; ++i) {
        cout << answer[i].second << ' ' << answer[i].first << endl;
    }

    return 0;
}