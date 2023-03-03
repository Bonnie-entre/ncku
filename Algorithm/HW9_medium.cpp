#include <iostream>
#include <queue>
#include <cstring>
using namespace std;
typedef pair<int,int> P;

int main(){
    int n, m, sx, sy, tx, ty;
    cin >> n >> m >> sx >> sy >> tx >> ty;
    sx-=1; sy-=1; tx-=1; ty-=1;
    int dx[4]={1,0,-1,0},dy[4]={0,1,0,-1};
    int d[n][m];
    int maze[n][m];
    for(int i=0; i<n; i++)
        for(int j=0; j<m; j++)
            cin >> maze[i][j];

    queue <P> q;
    memset(d,0,sizeof(d));
    q.push(P(sx,sy));
    d[sx][sy] = 1;
    while(q.size()){
        P p = q.front();
        q.pop();
        int nx = p.first, ny = p.second;
        if(nx==tx && ny==ty){
            break;
        }

        //push others into queue - breadth
        for(int i=0; i<4; i++){
            nx = p.first + dx[i];
            ny = p.second + dy[i];
            if(nx>=0 && ny>=0 && nx<n && ny<m && d[nx][ny]==0 && maze[nx][ny]==1){
                d[nx][ny]=d[p.first][p.second]+1;
                q.push(P(nx,ny));
            }
        }
    }

    if(d[tx][ty]!=0)
        cout << d[tx][ty]-1 << endl;
    else
        cout << -1  << endl;
    return 0;
}