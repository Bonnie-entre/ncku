#include<iostream>
using namespace std;

void Insert(int *ans, int end, int key);
void Heapify(int *ans, int end, int i);

int main(){
    int num;
    cin >> num;

    int ans[num], n;
    for(int i=0; i<num; i++){
        cin >> n;
        Insert(&ans[0], i, n);
    }   

    for(int i=0; i<num; i++){
        cout << ans[i] << " ";
    }
    return 0;
}

void Insert(int *ans, int end, int key){
    *(ans + end) = key;
    end++;
    Heapify(ans, end, end - 1);
}

void Heapify(int *ans, int end, int i){
    int parent = (i-1)/2;
    if (*(ans+parent) > 0) {
        
        if (*(ans+i) < *(ans+parent)) {
            swap(*(ans+i), *(ans+parent));
 
            Heapify(ans, end, parent);
        }
    }
}

// 6 
// 40 60 10 20 50 30
// 0  1  2  3  4  5
//


// 10  //i = 0

// 20 30 //2i+1=1, 2i+2=2

// 60 50 40 //2i+1=3 2i+2=4, 2i+1=5