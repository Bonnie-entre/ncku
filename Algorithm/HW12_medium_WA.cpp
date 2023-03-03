#include <iostream>
#include <map>
#include <vector>
#include <stack>
using namespace std;

class Graph{
    int V;

    vector<int>* node; //why pointer??
    // bool * store;

    // A function used by topologicalSort
    void topologicalSortUtil(int v, bool visited[], stack<int>& res, int father);

    public:
        Graph(int v);
        void addEdge(int v, int w);

        // prints a Topological Sort of
        // the complete graph
        void topologicalSort();
};

Graph::Graph(int v){
    this->V = v+1;
    node = new vector<int>[V];
    // store = new bool [V];
    // for(int i=0; i<V; i++)
    //     store[i] = false;
}

void Graph::topologicalSortUtil(int v, bool visited[], stack<int>& res, int father)    //vector<int> > & res, int father
{
    visited[v] = true;
 
    // Recur for all the vertices
    // adjacent to this vertex
    for (auto i : node[v])
        if (!visited[i])
            topologicalSortUtil(i, visited, res, v);
 
    // Push current vertex to stack
    // which stores result
    res.push(v);
    // res[father].push_back(v);
}

void Graph::topologicalSort()
{
    stack<int> res;
    // map<int, vector<int> > res;
 
    bool* visited = new bool[V];    //why pointer
    for (int i = 0; i < V; i++)
        visited[i] = false;
 
    // Call the recursive
    for (int i = V-1; i >=1; i--)
        if (visited[i] == false)
            topologicalSortUtil(i, visited, res, i);
 
    // Print contents of stack
    while (res.empty() == false) {
        cout << res.top() << " ";
        res.pop();
    }
    // for(auto r : res){
    //     cout << r.first << " ";
    //     for(auto v : r.second)
    //         cout << v << " ";
    // }
    cout << endl;
}

void Graph::addEdge(int x, int y){
    node[x].push_back(y);
}

int main(){
    int n, N;
    cin >> n >> N;
    while(!cin.eof()){
        Graph g(n);

        //Input Nodes
        int x, y;
        for(int i=0; i<N; i++){
            cin >> x >> y;
            g.addEdge(x,y);
        }

        g.topologicalSort();

        //next run
        cin >> n >> N;
    }

    return 0;
}