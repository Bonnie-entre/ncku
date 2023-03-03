#include<iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main(){
    long long num, n;
    cin >> num;
    if(num<2){
        cout << 0;
        return 0;
    }

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    vector <long long> data;
    for(long long i=0; i<num; i++){
        cin >> n;
        data.push_back(n);
    }

    sort(data.begin(), data.end());

    long long minus_max = 0;
    for(long long i=0; i<num-1; i++){
        if(data.at(i+1)-data.at(i)>minus_max){
            minus_max = data.at(i+1)-data.at(i);
        }
    }
    cout << minus_max;

    return 0;
}