#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <climits>
using namespace std;

struct Order{
    int num;
    int group;
    Order(int a, int b){
        num = a;
        group = b;
    }
};

bool compare(Order a, Order b) {
  return a.num < b.num;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int line;
    cin >> line;
    vector<Order> order;
    set<int> lost;
    for(int i=0; i<line; i++){
        int n, x;
        cin >> n;
        while(n--){
            cin >> x;
            Order o(x, i);
            order.push_back( o);
        }
        lost.insert(i);
    }

    sort(order.begin(), order.end(), compare);
    
    int min_diff = INT_MAX, a, b;
    set<int> need = lost;
    int start_i = 0, end_i = 1, diff = 0;
    for(int i = start_i; i <= end_i; i++)
        need.erase(order[i].group);
    
    while( start_i < order.size() && end_i < order.size() ){
        if(need.size()==0){
            if( order[end_i].num - order[start_i].num < min_diff){
                min_diff = order[end_i].num - order[start_i].num;
                a = order[start_i].num;
                b = order[end_i].num;
            }
            need = lost;
            while(order[++start_i].num == order[start_i-1].num){}
            while(end_i <= start_i)
                end_i++;

            //erase
            for(int i = start_i; i <= end_i; i++)
                need.erase(order[i].group);
        }
        else
            need.erase(order[++end_i].group);        
    }

    cout << a << " " << b << endl;

    return 0;
}