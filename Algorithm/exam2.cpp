#include <iostream>
#include <vector>
#include <map>

using namespace std;

// int main(){
//     ios_base::sync_with_stdio(false);
//     cin.tie(NULL);

//     int num;
//     cin >> num;
//     int numbers[num][2];
//     for(int i=0; i<num; i++){
//         cin >> numbers[i][0];
//         numbers[i][1] = 0;
//     }    

//     int x, index = 0;
//     map <int, int > mp;
//      for(int i=num-1; i>=0; i--){
//         mp[ numbers[i][0] ] = mp.size();
//     }
//     for(auto iter = mp.begin(); iter!=mp.end(); iter++){
//         cout << iter->first << " " << iter->second << endl;
//     }

//     return 0;
// }