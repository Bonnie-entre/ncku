#include<iostream>
#include <vector>
#include <map>
using namespace std;

long long int CountInversion(int *numbers, int front, int mid, int end){
    vector<int> temp;
    int left_i = front, right_i = mid;
    long long int counter =0;
    while(left_i < mid && right_i <= end){
        if( *(numbers+left_i) <= *(numbers+right_i)){
            temp.push_back( *(numbers+(left_i++)) );
        }
        else{
            temp.push_back( *(numbers+(right_i++)) );
            counter += (mid - left_i) %524287;
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

    return counter % 524287;
}

long long int MergeSort(int *numbers, int front, int end){
    long long int counter = 0;
    if(front<end){
        int mid = (front+end) / 2;
        counter += MergeSort(numbers, front, mid);
        counter += MergeSort(numbers, mid+1, end);
        counter += CountInversion(numbers, front, mid+1, end);
    }
    return counter% 524287;
}

int main()
{
    int num;
    cin >> num;

    int numbers[num];
    for(int i=0; i<num; i++){
        cin >> numbers[i];
    }    
    
    cout << MergeSort(&numbers[0], 0, num-1) % 524287;
    return 0;
}