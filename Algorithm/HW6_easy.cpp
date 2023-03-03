#include <iostream>
#include <map>
#include <vector>
using namespace std;

int main(){
    int n, x;
    cin >> n;

    map<int, int> m;
    for(int i=0; i<n; i++){
        cin >> x;
        m[x]++;     //!!
    }

    
    while(!m.empty()){  //!!
        vector<int> v;
        for(auto it=m.begin(); it != m.end();){
            v.push_back(it->first);
            if(--(it->second) == 0){
                auto e = it++;  //it++ is necessary!!
                m.erase(e);
            }
            else{
                it++;
            }
        }

        //output    //put here!!
        for(auto it = v.begin(); it != v.end(); it++){
            cout << *it << " ";
        }
        cout << endl;
    }

    return 0;
}