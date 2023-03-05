#include <stdio.h>
#include <stdbool.h>
#define n 5

bool visit(char [][n], int [][n], int, int);

bool visit(char maze[][n], int route[][n], int originX, int originY) 
{  
    const int dx[4] = {1, 0, -1, 0};    // 四種方向
    const int dy[4] = {0, 1, 0, -1};    
    //沒走過、範圍內、有路
    if( !route[originX][originY] && originX>=0 && originX<n && originY>=0 && originY<n && maze[originX][originY]=='r' )  {
        route[originX][originY]=1;

        if( !(originX==n-1 && originY==n-1) ){
            int i;
            for(i=0; i<4; i++){
                visit(maze, route, originX+dx[i], originY+dy[i]);
                if(route[n-1][n-1]==1) { break; }       //走到目的地
                if(i==3) { route[originX][originY]=0;  }    //這個點沒路走
            }
        }
    }
    return route[n-1][n-1];
}

int main(void) {
    char maze[n][n];
    int route[n][n];
    // initialize maze and route matrices
    for (int i=0; i<n; i++) {
        for (int j=0; j<n; j++) {
	        route[i][j]=0;
	        scanf("%c", &maze[i][j]);
	        getchar();
	    }
    }
    if (visit(maze, route, 0, 0)) { // (0,0) is a starting point
        for (int i=0; i<n; i++) {
	        for (int j=0; j<n; j++)
	            printf("%d ", route[i][j]);
	        printf("\n");
        }
    } else {
	    printf("Can't find the exit!");
    }
    return 0;
}


// int visit(int maze[][SIZE], Point start, Point end) {
//     if(!maze[start.x][start.y]) {
//          maze[start.x][start.y] = 1;
    //當不能到終點，又無路可走時，出發點為零
//          if(!maze[end.x][end.y] && 
//             !(visit(maze, pt(start.x, start.y + 1), end) || 
//               visit(maze, pt(start.x + 1, start.y), end) ||
//               visit(maze, pt(start.x, start.y - 1), end) || 
//               visit(maze, pt(start.x - 1, start.y), end))) {
//                  maze[start.x][start.y] = 0;
//          }
//     }
    //若終點到得了，會被標記1
//     return maze[end.x][end.y];
// }


//方法三
// int DFS(int x, int y, int target_x, int target_y, int d)
// {
//     if ( !(maze[x][y] == -1 || maze[x][y] > 0) ) {      //沒碰到牆壁或走過的路才會繼續
//         maze[x][y] = d; 
//         if ( !(x == target_x && y == target_y) ) {      //還沒走到目的地則繼續
//             for (int i=0; i<ACT; ++i)
//             {
//                 DFS(x + dx[i], y + dy[i], target_x, target_y, d + 1);
//                 if (maze[target_x][target_y] != 0)      //當以走到目的地時就不用再往其他方向走,所以跳出迴圈
//                     break; 
//             }
//             //當走到無路可走時,就會往回走,所以把目前這個點設為0,代表走到目的地時,不會顯示走過這個點
//             if(i == ACT)                                        
//                 maze[x][y] = 0;
//         }
//     }
//     return maze[target_x][target_y]; 
// }

//方法二<待修改
// route[originX][originY] = 1;
//     if( originX==n-1 && originY==n-1 ) { return true; }
//     if( originY+1 < n ) { visit(maze, route, originX, originY+1); }
//     if( originY-1 >=0 ) { visit(maze, route, originX, originY-1); }
//     if( originX+1 < n ) { visit(maze, route, originX+1, originY); }
//     if( originX-1 >=0 ) { visit(maze, route, originX-1, originY); }
//     route[originX][originY] = 0;
//     return false;

//方法二
// int visit(int i, int j) 
// { 
//  //該點走過，標記為1
//     maze[i][j] = 1; 
//  //走到終點，成功
//     if(i == endI && j == endJ)
//         success = 1; 
//  //向四個方向遞迴呼叫函式visit()
//     if(success != 1 && maze[i][j+1] == 0) visit(i, j+1); 
//     if(success != 1 && maze[i+1][j] == 0) visit(i+1, j); 
//     if(success != 1 && maze[i][j-1] == 0) visit(i, j-1); 
//     if(success != 1 && maze[i-1][j] == 0) visit(i-1, j); 
 
//  //該點走過，但沒成功，則該點重新置為0
//     if(success != 1) 
//         maze[i][j] = 0; 
    
//     return success; 
// }  

//方法一
//要怎麼改？
// bool visit(char maze[][n], int route[][n], int originX, int originY) 
// {
//     if( !maze[originX][originY] ){
//         route[originX][originY] = 1;
//     }
//     if( !maze[n-1][n-1] ){
//         if ( !( visit(maze, route, originX, originY+1 ) || 
//                 visit(maze, route, originX, originY-1 ) ||
//                 visit(maze, route, originX+1, originY ) ||
//                 visit(maze, route, originX-1, originY ) ))
//         {
//             route[originX][originY] = 0;
//         }
//     }     
//     return route[n-1][n-1];   
// }