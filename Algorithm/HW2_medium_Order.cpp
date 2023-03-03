#include <iostream>
// #include <vector>

using namespace std;

void Print(int space, int last, int num, int *nums, int *output){
      
}

int main(){
    int num;
    cin >> num;

    int nums[num];
    int output[6];
    for(int i=0; i<num; i++){
        cin >> nums[i];
    }
    int index[6] = {0, 1, 2, 3, 4, 5};

    //a5
    while(index[5] < num){ 
        for(int i=0; i<5; i++){
            cout << nums[i] << " "; 
        }
        for(int i=5; i<6 ;i++){
            cout << nums[ index[i] ] << " "; 
        }
        cout << endl;
        index[5]++;
    }


    //a4
    index[4]++; //5
    while((index[4]+1) < num){ 
        index[5] = index[4]+1; 
        while(index[5] < num){ 
            for(int i=0; i<4; i++){
                cout << nums[i] << " "; 
            }
            for(int i=4; i<6 ;i++){
                cout << nums[ index[i] ] << " "; 
            }
            cout << endl;
            index[5]++;
        }
        index[4]++; 
    }

    // a3
    index[3] = 4; 
    while((index[3] + 2) < num){
        index[4] = index[3]+1; 
        while((index[4]+1) < num){ 
            index[5] = index[4]+1; 
            while(index[5] < num){ 
                for(int i=0; i<3; i++){
                    cout << nums[i] << " "; 
                }
                for(int i=3; i<6 ;i++){
                    cout << nums[ index[i] ] << " "; 
                }
                cout << endl;
                index[5]++;
            }
            index[4]++; 
        }
        index[3]++; 
    }
    
    //a2
    index[2]++; //3 
    while((index[2] + 3) < num){
        index[3] = index[2]+1; 
        while((index[3] + 2) < num){
            index[4] = index[3]+1; 
            while((index[4]+1) < num){ 
                index[5] = index[4]+1; 
                while(index[5] < num){ 
                    for(int i=0; i<2; i++){
                        cout << nums[i] << " "; 
                    }
                    for(int i=2; i<6 ;i++){
                        cout << nums[ index[i] ] << " "; 
                    }
                    cout << endl;
                    index[5]++;
                }
                index[4]++; 
            }
            index[3]++; 
        }
        index[2]++;
    }

    //a1
    index[1]++; //2 
    while((index[1] + 4) < num){
        index[2] = index[1]+1; 
        while((index[2] + 3) < num){
            index[3] = index[2]+1; 
            while((index[3] + 2) < num){
                index[4] = index[3]+1; 
                while((index[4]+1) < num){ 
                    index[5] = index[4]+1; 
                    while(index[5] < num){ 
                        for(int i=0; i<1; i++){
                            cout << nums[i] << " "; 
                        }
                        for(int i=1; i<6 ;i++){
                            cout << nums[ index[i] ] << " "; 
                        }
                        cout << endl;
                        index[5]++;
                    }
                    index[4]++; 
                }
                index[3]++; 
            }
            index[2]++;
        }
        index[1]++;
    }

    //a0
    index[0]++; //2 
    while((index[0] + 5) < num){
        index[1] = index[0]+1;
        while((index[1] + 4) < num){
            index[2] = index[1]+1; 
            while((index[2] + 3) < num){
                index[3] = index[2]+1; 
                while((index[3] + 2) < num){
                    index[4] = index[3]+1; 
                    while((index[4]+1) < num){ 
                        index[5] = index[4]+1; 
                        while(index[5] < num){ 
                            for(int i=0; i<6 ;i++){
                                cout << nums[ index[i] ] << " "; 
                            }
                            cout << endl;
                            index[5]++;
                        }
                        index[4]++; 
                    }
                    index[3]++; 
                }
                index[2]++;
            }
            index[1]++;
        }


        index[0]++;
    }
    return 0;
}