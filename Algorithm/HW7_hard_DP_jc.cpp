#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;

struct  task_block{
    int score,deadline,spend;
    task_block( int cx,int cy,int cz) { score=cx, deadline=cy,spend=cz;};

};


struct  cmp{
    bool operator()(const task_block*a,const task_block* b) const
    {
        return a->deadline > b->deadline;   //big -> small, decreasing
    }
};


int main(){
    int n, max_dl = 0;
    int score,deadline,spend;
    cin >> n ;

    priority_queue<task_block*,vector<task_block*>,cmp> pq; //priotity queue will do !cmp

    for(int i = 0; i < n; i++){
        cin >> score >> deadline >> spend;
        max_dl = deadline > max_dl ? deadline : max_dl;
        pq.emplace(new task_block(score,deadline,spend));
    }
    vector<int> dp( max_dl+1,0);

    while(pq.size()){
        auto it = pq.top();
        pq.pop();
        for(int j = it->deadline; j >= it->spend; j--)
            dp[j] = max(dp[j], it->score + dp[j - it->spend]);
    }
    
    cout << *max_element(dp.begin(),dp.end());
    return 0;
}