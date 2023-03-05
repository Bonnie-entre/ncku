#include <stdio.h>
#include <iostream>
#include <fstream>
#include <queue>
using namespace std;
#define SIZE 100

ofstream ofs;

// Use BFS(array),and output the visit order
void BFS(int arr[][SIZE], int entry, int size){
    queue <int> q;
    q.push(entry);
    int count = 0;
    int r, path[size], record[size];
    for( int i=0; i<size; i++){
        path[i] = 0;
        record[i] = 0;
    }
    while(!q.empty()){
        r = q.front();
        path[count++] = r;
        record[r] = 1;
        q.pop();
        for(int i=0; i<size; i++){
            if( record[i]==0 && arr[r][i]==1 && r!=i ){
                q.push(i);
                record[i] = 1;
            }
        }
    }
    for( int i=0; i<size; i++){
        ofs << path[i] << " ";
    }
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
        
        // For Output
        filename[0] = 'o';
        filename[1] = 'u';
        ofs.open(filename);

        int dataset_num = 0;
        int count_dataset = 0;
        input_file >> dataset_num;
        while (count_dataset<dataset_num)
        {
            int row_num, entry;
            input_file >> row_num;
            input_file >> entry;

            int arr[SIZE][SIZE];
            for( int i=0; i< row_num; i++){
                for( int j=0; j<row_num; j++){
                    input_file >> arr[i][j];
                }
            }
            BFS(arr, entry, row_num);
            count_dataset++;
            ofs << "\n";
        }
        input_file.close();
        break;
    }
}


int main(){
    Input();

    return 0;
}