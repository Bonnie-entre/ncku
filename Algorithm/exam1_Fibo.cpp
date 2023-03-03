#include <iostream>
#include <vector>

using namespace std;
int main()
{
    long long fib[92];
    int n, i;

    fib[1] = 1;
    fib[2] = 1;
    for( i=3 ; i<=92 ; i=i+1 )
        fib[i] = fib[i-1] + fib[i-2];

    cin >> n;
    cout << fib[n+1] << endl;
    
    return 0;
}

// long long f(long long n)
// {
//     if( n==1 | n==2 )
//         return 1;
//     return f(n-1)+f(n-2);
// }

// int main()
// {
//     ios_base::sync_with_stdio(false);
//     cin.tie(NULL);
//     long long n;
//     cin >> n;
//     cout << f(n+1) << endl;
    

//     return 0;
// }