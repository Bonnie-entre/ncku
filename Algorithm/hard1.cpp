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

        return a->deadline > b->deadline;
    }
};


int main(){

    int n,maxdeadline=0;
    int score,deadline,spend;
    cin >> n ;

    //vector<task_block*> array;
    priority_queue<task_block*,vector<task_block*>,cmp> pq;

    for(int i = 0; i < n; i++){

        cin >>score>> deadline >> spend;
        if(deadline>maxdeadline)
            maxdeadline=deadline;
        pq.emplace(new task_block(score,deadline,spend));
    }
    vector<int> dp( maxdeadline+1,0);

    //sort(array.begin(), array.end(),cmp());

//    for(int i = 0; i < n; i++){
//        cout  << array[i]->score<< " "<< array[i]->deadline<< " "<< array[i]->spend << endl;
//
//    }
    while(pq.size()){
        auto it=pq.top();
        pq.pop();
        for(int j = it->deadline; j >= it->spend; j--)
            dp[j] = max(dp[j], it->score + dp[j - it->spend]);
    }
    cout<<*max_element(dp.begin(),dp.end());
    return 0;
}

//6
//20 2000 400
//40 1000 500
//40 3000 1000
//30 1300 400
//20 2000 700
//10 1000 100