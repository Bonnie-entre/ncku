#include <stdio.h>
#include <iostream>
#include <fstream>
#include <set>
#include <queue>
using namespace std;
#define SIZE 1000000

class Edge{
    public:
    int s;
    int t;
    int weight;

    Edge( int w, int s_i, int t_i){
        weight = w;
        s = s_i;
        t = t_i;
    }
};

set <int> record;
set <int> se[SIZE];

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
        cout << "Load file success." << endl;

        int v_num, v_sta;
        input_file >> v_num;

        Edge *edge[v_num];
        for( int i=0; i<v_num-1; i++)   
        {
            record.insert(i+1); //initialize set record

            int s, t, c;
            input_file >> s;
            input_file >> t;
            input_file >> c;
            Edge* e=NULL;
            e = new Edge(c,s,t);
            edge[i] = e;
            
            se[s].insert(t);
            se[t].insert(s);
        }
        input_file >> v_sta;
        record.insert(v_num);


        // function
        long long sum[SIZE] = {0};   
        queue <int> q;
        
        while( !se[v_sta].empty() ){    // start from v_star
            record.erase(v_sta);
            std::set<int>::iterator temp = se[v_sta].begin();
            q.push(*temp);

            se[v_sta].erase(*temp);

            if(*temp<v_sta){
                for(int i=0; i<v_num-1; i++){
                    if(edge[i]->s == *temp && edge[i]->t == v_sta ){
                        sum[*temp] = edge[i]->weight;
                        break;
                    }
                }
            }
            else{
                for(int i=0; i<v_num-1; i++){
                    if(edge[i]->t == *temp && edge[i]->s == v_sta ){
                        sum[*temp] = edge[i]->weight;
                        break;
                    }
                }
            }
        }

        while ( ! q.empty() )   // q have some waiting to go
        {
            int now = q.front();
            q.pop();

            //if record exist it，it should be executed
            if( record.find(now) != record.end() ) 
            {
                record.erase(now);

                //execute set. if set is empty, which means it has been gone through
                while( !se[now].empty() ){  
                    std::set<int>::iterator temp = se[now].begin();
                    if( record.find(*temp) != record.end() )    //if record exist it，it should be executed
                    {
                        q.push(*temp);
                        se[now].erase(*temp);
                        sum[*temp] += sum[now];

                        if(*temp<now){
                            for(int i=0; i<v_num-1; i++){
                                if(edge[i]->s == *temp && edge[i]->t == now ){
                                    sum[*temp] = edge[i]->weight;
                                    break;
                                }
                            }
                        }
                        else{
                            for(int i=0; i<v_num-1; i++){
                                if(edge[i]->t == *temp && edge[i]->s == now ){
                                    sum[*temp] += edge[i]->weight;
                                    break;
                                }
                            }
                        }
                    }
                    se[now].erase(*temp);
                }
            }
        }
        input_file.close();

        // Output
        ofstream ofs;
        filename[0] = 'o';
        filename[1] = 'u';

        ofs.open(filename);
        if (!ofs.is_open()) {
            cout << "Failed to open file.\n";
        } else {
            for( int i=1; i<=v_num; i++){
                ofs << i << " " <<  sum[i] << "\n";
            }
            ofs.close();
        }

        break;
    }
}

int main(){
    Input();
    return 0;
}