#include <iostream>
#include <string>
using namespace std;

int main(){
    int n;
    string s, t;
    cin >> n;
    int ans[n];
    for(int i=0; i<n; i++){
        cin >> s;
        cin >> t;
        int loop[t.length()];
        for(int j=0; j<t.length(); j++)
            loop[j] = 0;

        int si=0, ti=0, count=1;
        while(ti<t.length()){
            if(t[ti]==s[si]){
                // cout << t[ti] << " si=" << si << " count=" << count << endl;
                ti++;
                if(ti==t.length()){
                    ans[i] = count;
                    break;
                }
            }
            si++;
            if(si>=s.length()){
                si = 0;
                count++;
                if(loop[ti]){
                    ans[i] = -1;
                    break;
                }
                loop[ti] = 1;
            }
        }
    }

    for(int i=0; i<n; i++)
        cout << ans[i] << endl;

    // cout << t.length();
    return 0;
}