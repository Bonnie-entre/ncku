// 因為SCC的寫法 會卡數目極大的側資  //ref: geeksforgeeks.org/tarjan-algorithm-find-strongly-connected-components/?ref=lbp
// 用 Tarjan(), Slove() 會有五筆測資出錯    //ref: https://www.796t.com/content/1549413022.html
// 所以combine兩種寫法，好蠢QQ
#include <iostream> 
#include <cstring>  
#include <vector>  
#include <algorithm>  
#include <list>
#include <stack>
#define NIL -1
using namespace std;  
#define maxn 1001
vector<int> mp[maxn];  
int ans[maxn];  
int vis[maxn];  
int dfn[maxn];  
int low[maxn];  
int n,m, time_u, sig;  


// A class that represents an directed graph
class Graph
{
	int V; // No. of vertices
	list<int> *adj; // A dynamic array of adjacency lists

	// A Recursive DFS based function used by SCC()
	void SCCUtil(int u, int disc[], int low[],
				stack<int> *st, bool stackMember[]);
public:
    int ans;
	Graph(int V); // Constructor
	void addEdge(int v, int w); // function to add an edge to graph
	void SCC(); // prints strongly connected components
};

Graph::Graph(int V)
{
	this->V = V;
	adj = new list<int>[V];
    ans = 0;
}

void Graph::addEdge(int v, int w)
{
	adj[v].push_back(w);
}

// A recursive function that finds and prints strongly connected
// components using DFS traversal
// u --> The vertex to be visited next
// disc[] --> Stores discovery times of visited vertices
// low[] -- >> earliest visited vertex (the vertex with minimum
//			 discovery time) that can be reached from subtree
//			 rooted with current vertex
// *st -- >> To store all the connected ancestors (could be part
//		 of SCC)
// stackMember[] --> bit/index array for faster check whether
//				 a node is in stack
void Graph::SCCUtil(int u, int disc[], int low[], stack<int> *st,
					bool stackMember[])
{
	// A static variable is used for simplicity, we can avoid use
	// of static variable by passing a pointer.
	static int time = 0;

	// Initialize discovery time and low value
	disc[u] = low[u] = ++time;
	st->push(u);
	stackMember[u] = true;

	// Go through all vertices adjacent to this
	list<int>::iterator i;
	for (i = adj[u].begin(); i != adj[u].end(); ++i)
	{
		int v = *i; // v is current adjacent of 'u'

		// If v is not visited yet, then recur for it
		if (disc[v] == -1)
		{
			SCCUtil(v, disc, low, st, stackMember);

			// Check if the subtree rooted with 'v' has a
			// connection to one of the ancestors of 'u'
			// Case 1 (per above discussion on Disc and Low value)
			low[u] = min(low[u], low[v]);
		}

		// Update low value of 'u' only of 'v' is still in stack
		// (i.e. it's a back edge, not cross edge).
		// Case 2 (per above discussion on Disc and Low value)
		else if (stackMember[v] == true)
			low[u] = min(low[u], disc[v]);
	}

	// head node found, pop the stack and print an SCC
	int w = 0; // To store stack extracted vertices
	if (low[u] == disc[u])
	{
		while (st->top() != u)
		{
			w = (int) st->top();
			// cout << w << " ";
			stackMember[w] = false;
			st->pop();
		}
		w = (int) st->top();
		// cout << w << "\n";
        ans++;
		if(ans>1)
			return;
		stackMember[w] = false;
		st->pop();
	}
}

// The function to do DFS traversal. It uses SCCUtil()
void Graph::SCC()
{
	int *disc = new int[V];
	int *low = new int[V];
	bool *stackMember = new bool[V];
	stack<int> *st = new stack<int>();

	// Initialize disc and low, and stackMember arrays
	for (int i = 0; i < V; i++)
	{
		disc[i] = NIL;
		low[i] = NIL;
		stackMember[i] = false;
	}

	// Call the recursive helper function to find strongly
	// connected components in DFS tree with vertex 'i'
	for (int i = 1; i < V; i++){
		if (disc[i] == NIL)
			SCCUtil(i, disc, low, st, stackMember);
		if(ans>1)
			break;
	}
    if(ans>1)
        cout << 0 << endl;
    else    
        cout << 1 << endl;
}

void init(){  
    memset(low,0,sizeof(low));  
    memset(dfn,0,sizeof(dfn));  
    memset(vis,0,sizeof(vis));  
    for(int i=1;i<=n;i++)
        mp[i].clear();  
}  

void Tarjan(int u){  
    vis[u]=1;  
    low[u] = dfn[u] = time_u++;  

    for(int i=0;i<mp[u].size();i++){  
        int v=mp[u][i];  
        if(vis[v]==0)
            Tarjan(v);  
        if(vis[v]==1)
            low[u] = min(low[u],low[v]);  
    }  

    if(dfn[u]==low[u])  
        sig++;  
}  

void Slove(){  
    time_u = 1;
    sig = 0;  
    for(int i=1;i<=n;i++)  
    {  
        if(vis[i]==0)  
        {  
            Tarjan(i);  
        }  
    }  

    if(sig>1){
        cout << 0 << endl;
    }
    else    
        cout << 1 << endl;
}  

int main(){  
    while(true){
        init(); 
        
        cin >> n >>  m;
        if(n==0 && m==0)
            break;
        else if(m==0){
            cout << 0 << endl;
            continue;
        }

        int a, b, x;

        if(n>500){
            for(int i = 0; i < m; i++){ 
                cin >> a >> b >> x;  
                mp[a].push_back(b);

                if(x==2){  
                    mp[b].push_back(a);
                }
            }    

            Slove(); 
        }
        else{
            Graph g(n+1);
            for(int i = 0; i < m; i++){ 
                cin >> a >> b >> x;
                g.addEdge(a,b);

                if(x==2){
                    g.addEdge(b,a); 
                }
            }    

            g.SCC();
        }
        
    }

    return 0;
} 