#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int ans[300001];
struct Num{
    int x ,y ,order;
    Num(int a, int b, int to){
        x = a, y = b, order = to;
    }
};

bool cmp(const Num* b1, const Num* b2){
    if(b1->x < b2->x)
        return true;
    if(b1->x > b2->x)
        return false;
    return b1->y < b2->y;
}

void merge(vector<Num*> &a, int l, int m, int r){
    int i, j, k;
    int half1 = m - l + 1;  //how many in left pile
    int half2 = r - m;      //how many in right pile
    
    //pile up to left and right
    vector<Num*> L;
    vector<Num*> R;
    for(i = 0; i < half1; i++)
        L.push_back(a[l + i]);
    for(j = 0; j < half2; j++)
        R.push_back(a[m + 1 + j]);

    //combine into one in-order
    i = 0, j = 0, k = l;
    while(i < half1 && j < half2){
        if(L[i]->y <= R[j]->y){
            a[k] = L[i];
            i++;
        } else {
            a[k] = R[j];
            j++;
            ans[a[k]->order]+=i;    //calculate, the number a[k] bigger than how many numbers in left pile
        }
        k++;
    }
    // copy
    while(i < half1){
        a[k] = L[i];
        //a[k]->rank++;
        i++; k++;
    }
    while(j < half2){
        a[k] = R[j];
        ans[a[k]->order]+=i;    //calculate, the number a[k] bigger than how many numbers in left pile
        j++; k++;
    }
}
void MergeSort(vector<Num*> &a,int left, int right){
    int mid;
    if(left < right){
        mid = (left + right) / 2;
        MergeSort(a, left, mid);
        MergeSort(a, mid + 1, right);
        merge(a, left, mid, right);
    }
}


int main() {
    int line,x,y;
    cin >> line;

    vector<Num*> array;
    for(int i=0;i<line;i++){
        cin >> x >> y;
        array.push_back(new Num(x,y,i));
    }
    sort(array.begin(),array.end(),cmp);

    MergeSort(array, 0, line - 1);

    for(int i=0;i<line;i++)
        cout << ans[i] << " ";

    return 0;
}
