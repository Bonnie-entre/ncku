// C++ program to find articulation points in an undirected graph
// https://www.geeksforgeeks.org/articulation-points-or-cut-vertices-in-a-graph/?ref=gcse
// Learn for get the number ans, & order them by cmp function
// There r still 5 WA, but i don't know why
#include <bits/stdc++.h>
#include <map>
#include <set>
using namespace std;

vector<int> ans;

struct cmp{
    bool operator() (pair<int,int> &a, pair<int,int> &b)const {
        if(a.first==b.first)
            return a.second < b.second;
        return a.first > b.first;
    }
};

void APUtil(vector<int> adj[], int u, bool visited[],
			int disc[], int low[], int& time, int parent)
{
	visited[u] = true;
	disc[u] = low[u] = ++time;

	// Go through all vertices adjacent to this
	for (auto v : adj[u]) {

		if (!visited[v]) {
			APUtil(adj, v, visited, disc, low, time, u);

			low[u] = min(low[u], low[v]);

			if (parent != -1 && low[v] >= disc[u])  //if (parent != -1 && low[v] >= disc[u])
                ans[u]++;   // isAP[u] = true;
		}

		// Update low value of u for parent function calls.
		else if (v != parent)
			low[u] = min(low[u], disc[v]);
	}
}

void AP(vector<int> adj[], int V, int M)
{
	int disc[V] = { 0 };
	int low[V];
	bool visited[V] = { false };
	int time = 0, par = -1;

	for (int u = 0; u < V; u++)
		if (!visited[u])
			APUtil(adj, u, visited, disc, low,
				time, par);
}

// Utility function to add an edge
void addEdge(vector<int> adj[], int u, int v)
{
	adj[u].push_back(v);
	adj[v].push_back(u);
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int V, M, x, y;
    cin >> V >> M >> x >> y;
	vector<int> adj1[V];
    ans = vector<int>(V,1); //all initialize 1, because of its parent
    ans[0] = 0;
	// map<int, set<int>> mp;
    
    while(x!=-1 && y!=-1){
        addEdge(adj1, x, y);
        cin >> x >> y;
    }

	AP(adj1, V, M);

    //output ans in order
    vector<pair<int,int>> answer;
    for(int i=0; i<V; i++)
        answer.emplace_back(pair<int,int>{ans[i],i});

    sort(answer.begin(),answer.end(),cmp());


    for (int i = 0; i < M; ++i) {
        cout << answer[i].second << ' ' << answer[i].first << endl;
    }

	return 0;
}