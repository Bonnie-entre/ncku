#include <iostream>
#include <string>
#include <map>
using namespace std;

int main(){
    string str;
    cin >> str;

    int arr_count[62]={0};
    string arr_str[62];
    for(int i=0; i<str.length(); i++){
        int index;
        if(str[i]>='a' && str[i]<='z'){
            index = str[i] - 'a' + 36;
        }
        else if(str[i]>='0' && str[i]<='9'){
            index = str[i] - '0';
        }
        else{
            index = str[i] - 'A' + 10;
        }
        arr_count[index]++;
        arr_str[index]+=str[i];
    }
    
    //sort arr_count
    //if same count, the string will append in map
    map<int, string> mp;
    for(int i=0; i<62; i++){
        if(arr_count[i]>0){
            int key = arr_count[i];
            auto item = mp.find(key);
            if (item != mp.end()) {  //key exit
                mp[key] += arr_str[i];
            }
            else{   // not exit
                mp[arr_count[i]] = arr_str[i];
            }
        }
    }

    //output
    for(auto iter = mp.rbegin(); iter!=mp.rend(); iter++){
        cout << iter->second;   
    }
    return 0;
}