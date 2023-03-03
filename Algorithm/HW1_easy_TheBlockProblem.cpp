#include<iostream>
#include <vector>
using namespace std;

void Move(vector<int> v[], int a, int pos_ax, int Pos[][2]){
    int temp_n;
    while( (temp_n = v[pos_ax].back()) != a){
        v[temp_n].push_back(temp_n);
        v[pos_ax].pop_back();
        Pos[temp_n][0] = temp_n;
        Pos[temp_n][1] = v[temp_n].size()-1;
    }
}

int main()
{
    int num, cmd_num, cmd_count = 0;
    cin >> num >> cmd_num;

    int Pos[num+1][2]; //x(第幾個編號的原位),y(該編號原位上堆到第幾個)
    vector<int> v[num+1];
    for(int i=1; i<=num; i++){
        Pos[i][0] = i;
        Pos[i][1] = 0;
        v[i].reserve(1002);
        v[i].clear();
        v[i].push_back(i);
    }

    int a, b;
    string cmd_a, cmd_b;
    while(cmd_count != cmd_num){
        cmd_count ++;
        cin >> cmd_a >> a >> cmd_b >> b;

        if(a==b){
            continue;
        }
        else if(Pos[a][0]==Pos[b][0]){
            continue;
        }
        
        int pos_ax, pos_ay, pos_bx, temp_n;
        pos_ax = Pos[a][0];
        pos_ay = Pos[a][1]; //y(a在該編號原位上堆到第幾個
        pos_bx = Pos[b][0];
        Pos[a][0] = b;
        if(cmd_a == "move"){
            Move(v, a, pos_ax, Pos);
        }
        if(cmd_b == "onto"){
            Move(v, b, pos_bx, Pos);
        }

        // Finish the Movement
        int counter_insert = v[pos_ax].size() - pos_ay;   //a至最後一個元素共幾個數字，就要移幾次
        while(counter_insert){
            counter_insert--;
            int insert_num = v[pos_ax].at(pos_ay);
            // 更新欲插入數字的位置紀錄（第一次從a開始，也就是從原vector中間開始移動）
            Pos[ insert_num ][0] = Pos[ b ][0];
            Pos[ insert_num ][1] = v[pos_bx].size();
            // 在b插入數字，從a 刪掉該數字
            v[pos_bx].push_back(insert_num);
            v[pos_ax].erase(v[pos_ax].begin()+pos_ay);
        }
        counter_insert = 0;  
    }

    // Output
    for(int i=1; i<=num; i++){
        cout << i << ":";
        if( !v[i].empty() ){
            for(int j=0; j<v[i].size(); j++){
                cout << " " << v[i].at(j);
            }  
        }
        cout << endl;
    }

    return 0;
}

// move 1 onto 3
// move 2 over 3
// move 4 over 3
// move 5 over 4

// 10 8
// move 1 onto 3
// move 2 over 1
// pile 3 onto 5
// move 4 onto 5      
// move 6 over 8
// pile 7 over 8
// move 6 onto 10
// move 10 onto 6