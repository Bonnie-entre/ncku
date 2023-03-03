#include <iostream>
#include <climits>
using namespace std;


int main(){
    int n;
    cin >> n;

    int length[n], lengthR[n], s[n];
    for (int i=0; i<n; i++) 
        length[i] = lengthR[i] = 1;

    for (int i=0; i<n; i++){
        cin >> s[i];
        for (int j=0; j<i; j++)
            if (s[j] < s[i])
                length[i] = max(length[i], length[j] + 1);
    }

    for (int i=n-1; i>=0; i--)
        for (int j=n-1; j>i; j--)
            if (s[j] < s[i])
                lengthR[i] = max(lengthR[i], lengthR[j] + 1);
    
    
    // ans
    for (int i=0; i<n; i++)
        length[i] = n - (length[i] + lengthR[i] - 1);

    int l = INT_MAX;
    for (int i=0; i<n; i++)
        l = min(l, length[i]);
        
    cout << l << endl;
    return 0;
}