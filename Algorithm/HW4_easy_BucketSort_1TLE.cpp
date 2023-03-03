#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
// 1 4 7 15 19


long long bucket_sort(long long data[], long long num, long long bucket_n, long long interval) { 
    vector<long long> buckets[bucket_n];
    
    //put data into their bucket
	for(long long i=0; i<num; i++){
        buckets[ data[i] / interval].push_back(data[i]);
    }
    
    //sort each bucket 
    for (long long i = 0; i < bucket_n; i++){
        if(buckets[i].size()>1){
        sort(buckets[i].begin(), buckets[i].end());
        }
    }
    //Calculte the ans
    long long minus_max = 0, last;
	 for (long long i = 0; i < bucket_n; i++){
		if (buckets[i].size() > 0) {
            for(long long k=0; k<buckets[i].size(); k++){
                if( (i!=0 | k!=0) && (buckets[i].at(k)-last) > minus_max ){
                    minus_max = buckets[i].at(k)-last;
                }
                last = buckets[i].at(k);
                // cout << i<< ":last=" << last << ", minus=" << minus_max << endl;
			}
		}
	}

    //output for ckeck
    // for (long long i=0; i< bucket_n; i++) {
    //     for(long long j=0; j<buckets[i].size(); j++){
    //         cout << buckets[i].at(j) << " ";
    //     }
    //     cout << endl;
    // }
    return minus_max;
    // return 0;
}

int main(){
    long long num;
    cin >> num;
    if(num<2){
        cout << 0;
        return 0;
    }

    ios_base::sync_with_stdio(false); 
    cin.tie(NULL);
    long long data[num];
    cin >> data[0];
    long long max = data[0], min = data[0];
    for(long long i=1; i<num; i++){
        cin >> data[i];
        if(data[i]>max){
            max = data[i];
        }
        if(data[i]<min){
            min = data[i];
        }
    }
    
    long long interval = (max - min) / (num-1);
    cout << bucket_sort(data, num, max/interval+1, interval); 
    return 0;
}
//5
// 3 82 2 34 44