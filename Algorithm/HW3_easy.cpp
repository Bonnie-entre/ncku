#include<iostream>
#include <vector>
using namespace std;

void Merge(int *numbers, int front, int mid, int end){
    vector<int> temp;
    int left_i = front, right_i = mid;
    while(left_i < mid && right_i <= end){
        if( *(numbers+left_i) <= *(numbers+right_i)){
            temp.push_back( *(numbers+(left_i++)) );
        }
        else{
            temp.push_back( *(numbers+(right_i++)) );
        }
    }
    while(left_i < mid){
        temp.push_back( *(numbers+(left_i++)) );
    }
    while(right_i <= end){
        temp.push_back( *(numbers+(right_i++)) );
    }
    for(int i=0; i<temp.size(); i++){
        *(numbers+front+i) = temp.at(i);
    }
}

void MergeSort(int *numbers, int front, int end){
    long long int counter = 0;
    if(front<end){
        int mid = (front+end) / 2;
        MergeSort(numbers, front, mid);
        MergeSort(numbers, mid+1, end);
        Merge(numbers, front, mid+1, end);
    }
}

int main(){
    int num;
    cin >> num;

    int numbers[num];
    for(int i=0; i<num; i++){
        cin >> numbers[i];
    }  

    MergeSort(&numbers[0], 0, num-1);
    for(int i=0; i<num; i++){
        cout << numbers[i] << " ";
    }
    return 0;
}