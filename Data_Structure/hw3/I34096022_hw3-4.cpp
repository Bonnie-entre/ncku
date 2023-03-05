#include <iostream>
#include <fstream>
#include <vector>
#include<algorithm>
using namespace std;
#define SIZE 10000
    
struct Edge
{
int u, v;                                
int cost;                                
};
Edge edge[SIZE];

// Compare function
bool cmp(Edge a, Edge b)
{
return a.cost < b.cost;
}

// return where x is
int findFather(vector<int> father, int x)
{
int a = x;
while (x != father[x])
x = father[x];
while (a != father[a]) {
int z = a;
a = father[a];
father[z] = x;
}
return x;
}

// Kruskal to get the tree
int Kruskal(int n, int m, Edge edge[])
{
    vector<int> father(n);                                 
    int ans = 0;                                           //sum of edges
    int NumEdge = 0;                                       //the minimum of edges
    for (int i = 0; i < n; i++  )                          //initialize
    father[i] = i;
    sort(edge, edge+m, cmp);                         //sort the edge by weight

    for (int i = 0; i < m;   i++)                           
    {
        int faU = findFather(father, edge[i].u);           //find where u is
        int faV = findFather(father, edge[i].v);           //find where v is
        if (faU != faV) {                                  //if not in the same set
            father[faU] = faV;                             //combine
            ans  += edge[i].cost;
            NumEdge++;                              
            if (NumEdge == n - 1)                          //end
                break;
        }
    }
    if (NumEdge != n - 1)                                  
        return -1;
    else
        return ans;                                     
}

// Load the input file, and execute the command function
void Input(){
    char filename[100]={0};  //Input fileName
    while(1){
        cout << "Please input the file: " ;
        cin >> filename;
        ifstream input_file(filename);
        if (!input_file.is_open()) {
            cout<<"fail to open the file！"<<endl; 
            continue;
        }
        cout << "Load file success." << endl << endl;

        int e = 0, v = 0;
        input_file >> v;
        input_file >> e;

        for( int i=0; i< e; i++){
            input_file >> edge[i].u;
            input_file >> edge[i].v;
            input_file >> edge[i].cost;
        }
        input_file.close();

        int res = Kruskal(v, e, edge);

        // Output
        ofstream ofs;
        filename[0] = 'o';
        filename[1] = 'u';
        ofs.open(filename);
        ofs << res << endl;
        ofs.close();
        
        break;
    }
}

int main(){
    Input();

    return 0;
}