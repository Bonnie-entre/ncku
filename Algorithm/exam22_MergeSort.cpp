#include<iostream>
#include <vector>
#include <map>
using namespace std;

vector <int> q(100000);

void CountInversion(vector<pair<int,int>> &numbers, int front, int mid, int end){
    vector<pair<int,int>>  tempL;
    vector<pair<int,int>>  tempR;
    int left_i = 0, right_i=0, k = front;

    for(int i = 0; i < (mid-front+1); i++)
        tempL.push_back(numbers[front + i]);
    for(int j = 0; j < (end-mid); j++)
        tempR.push_back(numbers[mid + 1 + j]);


    // long long int counter =0;
    while(left_i < (mid-front+1) && right_i < (end-mid)){
        if(tempL[left_i].first <= tempR[right_i].first){
            numbers[k] = tempL[left_i++];
            q[numbers[k].second] += right_i;
            // temp.push_back( numbers[left_i++] );
        }
        else{
            numbers[k] = tempR[right_i++];
            // temp.push_back( numbers[right_i++] );
        }
        k++;
    }

    while(left_i < mid-front+1){
        numbers[k] = tempL[left_i++];
        q[numbers[k].second] += right_i;
        k++;
        // temp.push_back( numbers[left_i++] );
    }
    while(right_i < end-mid){
        numbers[k] = tempR[right_i++];
        k++;
        // temp.push_back( numbers[right_i++] );
    }

    // for(int i=0; i<temp.size(); i++){
        
    //     // numbers[front+i] = temp.at(i);
    // }

}

void MergeSort(vector<pair<int,int>> &arr, int front, int end){
    // long long int counter = 0;
    if(front<end){
        int mid = (front+end) / 2;
        MergeSort(arr, front, mid);
        MergeSort(arr, mid+1, end);
        CountInversion(arr, front, mid, end);
    }
}

int main()
{
    int num;
    cin >> num;

    vector<pair<int,int>> arr(num+1);
    for(int i=0;i<num;i++){
        cin >> arr[i].first;
        arr[i].second=i;
    }
    MergeSort(arr, 0, num - 1);
    
    // output
    for (int i = 0; i < num; i++) {
        cout << q[i] << " ";
    }
    
    return 0;
}