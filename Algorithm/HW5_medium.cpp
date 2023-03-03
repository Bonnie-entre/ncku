#include <iostream>
#include <map>
#include <set>
#include <string>
using namespace std;

int main(){
    // ios_base::sync_with_stdio(false);
    // cin.tie(NULL);
    int n, k;
    cin >> n >> k;

    //input & count
    map <string, int> mp_count;
    for(int i=0; i<n; i++){
        string key;
        cin >> key;
        auto item = mp_count.find(key);
        if (item != mp_count.end()) {  //key exit
            mp_count[key] ++;
        }
        else{   // not exit
            mp_count[key] = 1;
        }
    }

    //order
    map <int, set<string> > mp;
    for(auto iter = mp_count.begin(); iter!=mp_count.end(); iter++){
        int key = iter->second;     //key is count number, may duplicate
        auto item = mp.find(key);
        if (item != mp.end()) {  
            mp[key].insert(iter->first);    //string in set would order itself
        }
        else{   //not exit
            mp[iter->second].insert(iter->first);  
        }
    }

    //output
    int count_acu = 0, last_ca = 0;
    for(auto iter = mp.rbegin(); iter!=mp.rend(); iter++){     //reverse for decending to quickly output bigger one
        count_acu += iter->second.size();
        if(k<=count_acu){
            int i = 1;
            for(auto iter_s = iter->second.begin(); iter_s!=iter->second.end(); iter_s++, i++){
                if(i==k-last_ca){
                    cout << *iter_s << endl;  
                    return 0;
                }
            }
        }
        last_ca = count_acu; 
    }
    return 0;
}