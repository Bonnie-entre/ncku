#include <iostream>
using namespace std;

void Heapify(int arr[], int n, int i)
{
    int smallest = i; // Initialize largest as root
    int l = 2 * i + 1; // left = 2*i + 1
    int r = 2 * i + 2; // right = 2*i + 2
 
    // If left child is larger than root
    if (l < n && arr[l] < arr[smallest])
        smallest = l;
 
    // If right child is larger than largest so far
    if (r < n && arr[r] < arr[smallest])
        smallest = r;
 
    // If largest is not root
    if (smallest != i) {
        swap(arr[i], arr[smallest]);
 
        // Recursively heapify the affected sub-tree
        Heapify(arr, n, smallest);
    }
}

int main(){
    int num;
    cin >> num;

    int arr[num];
    for(int i=0; i<num; i++){
        cin >> arr[i];
    }

    // Build heap (rearrange array)
    for (int i = num / 2 - 1; i >= 0; i--){
        Heapify(arr, num, i);
    }

    // Print array
    for(int i=0; i<num; i++){
        cout << arr[i] << " ";
    }
    return 0;
}