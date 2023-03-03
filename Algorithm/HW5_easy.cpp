#include <iostream>
#include <string>
using namespace std;
 
struct data{
    double concentrate;
    string name;
};

void Swap(data *a, data *b){
    data temp = *a;
    a->concentrate = b->concentrate;
    a->name = b->name;
    b->concentrate = temp.concentrate;
    b->name = temp.name;
}

// Standard partition process of QuickSort().
// It considers the last element as pivot
// and moves all smaller element to left of
// it and greater elements to right
int partition(data arr[], int l, int r)
{
    Swap(&arr[r], &arr[(l+r)/2]);   //to improve the worst case of quick sort(not always take the rightest one as pivot)

    double x = arr[r].concentrate;
    int i = l;
    for (int j = l; j <= r - 1; j++) {
        if (arr[j].concentrate <= x) {
            Swap(&arr[i], &arr[j]);
            i++;
        }
    }
    Swap(&arr[i], &arr[r]);
    return i;
}
 
// This function returns k'th smallest
string kthSmallest(data arr[], int l, int r, int k)
{
    int index = partition(arr, l, r);

    // If position is same as k
    if (index-l == k)
        return arr[index].name;

    if (index - l > k)
        return kthSmallest(arr, l, index - 1, k);

    return kthSmallest(arr, index + 1, r,
                        k - index + l - 1);
    
}
 
int main()
{   
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, k;
    cin >> n >> k;
    data arr[n];

    int a, b, c;
    for(int i=0; i<n; i++){
        cin >> a >> b >> c >> arr[i].name;
        arr[i].concentrate = c / (double) (a+b+c);
    }

    cout << kthSmallest(arr, 0, n - 1, n-k);    //index = n - k (kth bigger = (n-k)th smaller)

    //check
    // cout << endl;
    // for(int i=0; i<n; i++){
    //     cout << arr[i].concentrate << " " << arr[i].name << endl;        
    // }
    return 0;
}