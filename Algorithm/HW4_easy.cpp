#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
#define NUM 10

long long bucket_sort(long long data[], long long num, long long bucket_n) { 
    vector<long long> buckets[bucket_n];
	for(long long i=0; i<num; i++)
        buckets[ data[i] / NUM].push_back(data[i]);

    long long minus_max = 0;
    long long last;
	for (long long i = 0; i < bucket_n; i++) {
		long long bucketSize = buckets[i].size();
		if (bucketSize == 1) {   //at least 1 element in bucket
            if( i != 0 && (buckets[i][0]-last) > minus_max){
                minus_max = buckets[i][0]-last;
            }
            last = buckets[i][0];
        }
		else if (bucketSize > 1) { //at least 2 element in bucket, order them
            sort(buckets[i].begin(), buckets[i].end());

            //Calculte the ans
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
}

int main(){
    long long num,n;
    cin >> num;
    if(num<2){
        cout << 0;
        return 0;
    }

    ios_base::sync_with_stdio(false); 
    cin.tie(NUL#include <iostream>
#include <vector>
#include <climits>
using namespace std;
// 1 4 7 15 19
// ios_base::sync_with_stdio(false); 
// cin.tie(NULL);

long long bucket_sort(long long data[], long long num, long long bucket_n, long long interval) { 
    long long arr_max[bucket_n], arr_min[bucket_n];
    for(int i=0; i<bucket_n; i++){
        arr_max[i] = INT_MIN;
        arr_min[i] = INT_MAX;
    }
    
    //put data into their bucket
	for(long long i=0; i<num; i++){
        long long index = data[i] / interval;
        if( data[i] > arr_max[index] ){
            arr_max[index]  = data[i];
        }
        if( data[i] < arr_min[index] ){
            arr_min[index]  = data[i];
        }
    }
    
    // cout << "check" << endl;
    // for(int i=0; i<bucket_n; i++){
    //     cout << i <<":max=" << arr_max[i] << "," << arr_min[i] << endl;
    // }

    //Calculte the ans
    long long minus_max = 0;
    for(int j=0, i=1; i<bucket_n; ){
        if(arr_min[i]==INT_MAX){
            i++;
            if( (arr_min[i]-arr_max[j]) > minus_max){
                minus_max = arr_min[i]-arr_max[j]; 
            }
            i++;
            j+=2;
        }
        else{
            if( (arr_min[i]-arr_max[j]) > minus_max){
                minus_max = arr_min[i]-arr_max[j]; 
            }
            i++; 
            j++;
        }
    }

    return minus_max;
}

int main(){
    long long num;
    cin >> num;
    if(num<2){
        cout << 0;
        return 0;
    }

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
// 3 82 2 34 44L);
    long long data[num], max = 0;
    for(long long i=0; i<num; i++){
        cin >> data[i];
        if(data[i]>max){
            max = data[i];
        }
    }
    
    cout << bucket_sort(data, num, max/NUM+1); //long long bucket_n = max/10 + 1; //number of bucket
    return 0;
}
//5
// 3 82 2 34 44