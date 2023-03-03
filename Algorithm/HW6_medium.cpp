#include <iostream>
#include <string>
#include <algorithm>
using namespace std;


int main(){
    int num;
    cin >> num;

    while(num){
        int Max = 0, stone, d, count_s=0, last1 = 0, last2 = 0;
        cin >> stone >> d;
        for(; stone>0; stone--){
            string s;
            int pos;
            cin >> s >> pos;
            if(s=="b"){
                Max = max(Max, pos-last1);
                Max = max(Max, pos-last2);
                last1 = last2 = pos;
                count_s = 0;
            }
            else{
                ++count_s;
                if(count_s%2==1){
                    Max = max(Max, pos-last1);
                    last1 = pos;
                }
                else{
                    Max = max(Max, pos-last2);
                    last2 = pos;
                }
            }
        }
        Max = max(Max, d-last1);
        Max = max(Max, d-last2);

        cout << Max << endl;
        num--;
    }

    return 0;
}