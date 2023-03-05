//
//  main.cpp
//
//  Created by 蔡易妏 on 2021/10/21.
//

#include <iostream>
using namespace std;
#include <iostream>
#include <fstream>
#include <typeinfo>
#include <stdlib.h>
#define SIZE 17

typedef struct
{
    int x,y;
}Pos;

typedef struct
{
    Pos start,end;
    char mazeChar[SIZE][SIZE];
    int mazeMark[SIZE][SIZE];
}Maze;


//this function works for loading the file maze.txt.
//in the same time, tansfer the input charArray into the intArray, so that we can easily mark them afterward.
//in while-loop, if file cannot load, you can keep trying untill succeed.
void Input( Maze &m ){
    char fileName[60];  //Input fileName
    
    while(1){
        cout << "enter filename：" ;
        cin >> fileName;
        ifstream inFile;
        inFile.open(fileName);
        
        if(!inFile.is_open()) {cout<<"fail to open the file！"<<endl;}
        else {
            for(int i = 0; i < SIZE; i++)
                {
                    for(int j = 0; j < SIZE; j++)
                    {
                        inFile>>m.mazeChar[i][j];
                        
                        if (m.mazeChar[i][j] == 48) { m.mazeMark[i][j] = 0; } //use ASCII Code
                        else { m.mazeMark[i][j] = 1; }
                        cout<<m.mazeMark[i][j];
                    }
                    cout<<endl;
                }
            inFile.close();
            
            break;
        }
    }
    
}


//this function called by function MazePath() works for identifying which one is rat's next position, or the road is closed.
//if there is path to go, the function will return next position's array element x,y.
//if not, mark next position's  x,y=(-1,-1). then, in function MazePath() will recognize it as road closed.
Pos Go(Maze m, Pos curpos)
{
    //cout << "Into MazePath-Go()" << endl; //ForDebug
    Pos nextpos;
    
    //NoRoad
    nextpos.x = -1;
    nextpos.y = -1;
    
    int x,y;
    x = curpos.x;
    y = curpos.y;
    
    //2-dimentionArry, x-down y-right
    if(m.mazeMark[x][y+1] == 0)//right
    {
        nextpos.x = x;
        nextpos.y = y+1;
    }
    else if(m.mazeMark[x+1][y] == 0)//down
   {
       nextpos.x = x+1;
       nextpos.y = y;
   }
    else if(m.mazeMark[x][y-1] == 0)//left
    {
        nextpos.x = x;
        nextpos.y = y-1;
    }else if(m.mazeMark[x-1][y] == 0)//up
    {
        nextpos.x = x-1;
        nextpos.y = y;
    }
    return nextpos;
}


//this function called by main() works for figuring out whether there is a road to escape or not and output the result.
//first, curpos means where rat is standing, and call the finction Go() to identify whether there is a path to go through. if yes, that would be rat's next curpos.
//in do-loop, use if-else to identify whether rat is standing at end position(push curpos into stack, and break the loop)? can go through it(push curpos into stack, go to nexpos)? road close(back to last position or end the do-loop)?   and record in mazeMarkArray[][] according to different situation.
//finally, output the result. if stack_empty(), Failed to escape. if not, use temp_stack to turn the order in path_stack into the right one and output it.
void MazePath(Maze m){
    //cout << "Into MazePath" << endl;  //ForDebug
    Pos curpos,nextpos;
    stack<Pos> path_stack;  //pathRecord
    stack<Pos> pathAll_stack;    //pathRecord including backwards
    curpos = m.start;
    
    //Find the road
    do{
        //cout << "Into MazePath-do, count: " << count << endl;  //ForDebug
        
        nextpos = Go(m,curpos);
        //cout << count << ":" <<"nextpos: "<<nextpos.x<<" "<<nextpos.y<<endl; //Reviex all path including backwards  //ForDebug
        //backCount++;  //ForDebug
        
        if(curpos.x == m.end.x && curpos.y == m.end.y)  //Now is End
        {
            path_stack.push(curpos);
            pathAll_stack.push(curpos);
            m.mazeMark[curpos.x][curpos.y] = -1;    //HaveGone mark-1
            break;
        }
        else if(nextpos.x != -1) //go through
        {
            path_stack.push(curpos);
            pathAll_stack.push(curpos);
            m.mazeMark[curpos.x][curpos.y] = -1;    //HaveGone mark-1
            curpos = nextpos;   //go to next step
        }
        else
        {
            m.mazeMark[curpos.x][curpos.y] = -2;    //RoadClose
            pathAll_stack.push(curpos);     //though there is no road for next step, and have to backwards, the rat still have gone through
            curpos = path_stack.top();
            path_stack.pop();   //Delete, go back to last step, find another direction  //Backward
            //backCount--;  //ForDebug
            //cout << "   Go back to" << backCount << ":" << curpos.x<<" "<<curpos.y<<endl; //ForDebug
            
            
            //when go back to first step, there is still other path to go; however, the start position has been pop and the stack is empty
            if (curpos.x == m.start.x && curpos.y == m.start.y && path_stack.empty()){
                nextpos = Go(m,curpos);
                if ( nextpos.x != -1 ) {
                    path_stack.push(curpos);
                    pathAll_stack.push(curpos); //Lets try
                    m.mazeMark[curpos.x][curpos.y] = -1;    //HaveGone mark-1
                    curpos = nextpos;   //go to next step
                }
            }
        }
    }while(!path_stack.empty());
        
    
    // Output result
    if(path_stack.empty()) {
        cout<<"Failed to escape."<<endl;
    }
    else{
        stack<Pos>tmp_stack;
        int n = -1;
        
        //Because stack FILO，so use texp_stack to turn the right order
        while(!pathAll_stack.empty())
        {
            curpos = pathAll_stack.top();
            pathAll_stack.pop();
            tmp_stack.push(curpos);
       }
       
       while(!tmp_stack.empty())
        {
            n++;
            curpos = tmp_stack.top();
            cout << n << "：" << curpos.x << "," << curpos.y << endl;
            tmp_stack.pop();
            m.mazeMark[curpos.x][curpos.y] = n;
       }
        cout<<"successfully escape!!"<<endl;
    }
}

int main(int argc, const char * argv[]) {
    
    Maze m;
    Input(m);   //Input Maze
    
    //keep entering the position pairs until (-1,-1)
    m.start.x =0;
    m.start.y =0;
    while (1){
        cout <<  "enter start position：";
        cin >>  m.start.x >> m.start.y;
        
        if (m.start.x== -1 && m.start.y == -1) {
            cout << "end the code." << endl;
            break;
            
        }
        cout <<  "enter exit position：";
        cin >>  m.end.x >> m.end.y;
        
        //cout << "before MazePath(m)" << endl; //ForDebug
        MazePath(m);
    }
    
    
    
    return 0;
}
