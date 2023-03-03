#include <iostream>
using namespace std;

void Heapify(int *arr, int i){
    int parent = (i-1)/2;
    if(parent>=0){
        if( *(arr+i) < *(arr+parent)){
            swap( *(arr+i), *(arr+parent));
            if(parent>0){
                Heapify(arr, parent);
            }
        }
    }
}

int main(){
    int num;
    cin >> num;

    int arr[num];
    for(int i=0; i<num; i++){
        cin >> arr[i];
    }

    for(int i=1; i<num; i++){
        Heapify(&arr[0], i);
    }

    for(int i=0; i<num; i++){
        cout << arr[i] << " ";
    }
    return 0;
}