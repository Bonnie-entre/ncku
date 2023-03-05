#include <stdio.h>
#include <iostream>
#include <fstream>
#include <stack>
using namespace std;
#define SIZE 100

ofstream ofs;

// Use DFS(array),and output the visit order
void DFS( int arr[][SIZE], int entry, int size ){
    int  record[size], path[size];
    for(int i=0; i<size; i++){
        record[i] = 0;
        path[size] = 0;
    }

    bool back = false;
    int back_count = 0;
    int count = 1;
    int r = entry;
    path[0] = entry;
    record[r] = 1;
    while( count<size ){

        for( int i=0;i<size; i++){
            if(record[i]==0 && arr[r][i]==1 && i!=r){
                record[i] = 1;
                path[count] = i;
                r = i;
                i = size;   //break;
                count++;
                if(back){
                    back = false;
                }
            }
            if( i==size-1 && back){
                r = path[--back_count];
            }
            if(i==size-1 && !back){
                r = path[count-2];
                back_count = count-2;
                back = true;
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
            DFS(arr, entry, row_num);
            count_dataset++;
            ofs << "\n";
        }
        input_file.close();
        ofs.close();
        break;
    }
}

int main(){
    Input();

    return 0;
}