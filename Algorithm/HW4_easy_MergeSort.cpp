#include<iostream>
#include <vector>
#include <climits>
using namespace std;

void CountInversion(long long *numbers, long long front, long long mid, long long end, long long num){
    vector<long long> temp;
    long long left_i = front, right_i = mid;
    long long  minus_max = 0, last = INT_MAX;
    if(front==0 && end==num-1){ //the last order run
        // for(long long i=0; i< num; i++){
        //     cout << *(numbers+i) << " ";
        // } cout << endl;
        while(left_i < mid && right_i <= end){
            if( *(numbers+left_i) <= *(numbers+right_i)){
                // temp.push_back( *(numbers+(left_i)) );
                if( (*(numbers+left_i)-last) > minus_max ){
                    minus_max = *(numbers+left_i)-last;
                }
                last = *(numbers+left_i);
                left_i++;
            }
            else{
                // temp.push_back( *(numbers+(right_i)) );
                if( (*(numbers+right_i)-last) > minus_max ){
                    minus_max = *(numbers+right_i)-last;
                }
                last = *(numbers+right_i);
                right_i++;
            }
        }
        while(left_i < mid){
            // temp.push_back( *(numbers+(left_i)) );
            if( (*(numbers+left_i)-last) > minus_max ){
                minus_max = *(numbers+left_i)-last;
            }
            last = *(numbers+left_i);
            left_i++;
        }
        while(right_i <= end){
            // temp.push_back( *(numbers+(right_i)) );
            if( (*(numbers+right_i)-last) > minus_max ){
                minus_max = *(numbers+right_i)-last;
            }
            last = *(numbers+right_i);
            right_i++;
        }
        // for(long long i=0; i< num; i++){
        //     cout << temp.at(i) << " ";
        // } 
        cout << minus_max;;
    }
    else{
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
        for(long long i=0; i<temp.size(); i++){
            *(numbers+front+i) = temp.at(i);
        }
    }
}

void MergeSort(long long *numbers, long long front, long long end, long long num){
    if(front<end){
        long long mid = (front+end) / 2;
        MergeSort(numbers, front, mid, num);
        MergeSort(numbers, mid+1, end, num);
        CountInversion(numbers, front, mid+1, end, num);
    }
}

int main()
{
    long long num;
    cin >> num;
    if(num<2){
        cout << 0;
        return 0;
    }

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    long long numbers[num];
    for(long long i=0; i<num; i++){
        cin >> numbers[i];
    }    

    MergeSort(&numbers[0], 0, num-1, num);
    return 0;
}