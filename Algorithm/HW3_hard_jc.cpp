#include<iostream>
#include<vector>
#include<list>
#include <algorithm>
#include <map>
using namespace std;

int mini=INT16_MAX;
int a, b;

struct element{
    int value,belong;
    element (int x, int y):
        value(x), belong(y){}

};


bool cmp(const element *b1, const element *b2){
    return b1->value < b2->value;
}

void finding(vector<element*> array, list<element*> check, int num , int all){
    int c[501];
    for(int i=0;i<501;i++)
        c[i]=0;

    list<element*>::iterator it;
    for(int i=0; i<all ;i++){
        element x(0,0);
        x.value = array[i]->value;
        x.belong = array[i]->belong;

        if(c[array[i]->belong]!=0){
            it=check.begin();
            while(1){
            if((*it)->belong ==array[i]->belong){
                check.erase(it);    //erase it so that we can get the short one
                break;
            }
            it++;
            }
        }

        //check contains the remain chain
        check.emplace_back(new element(array[i]->value,array[i]->belong));
        c[array[i]->belong]++;

        //compare the match one
        if(check.size()==num)
            if((check.back()->value-check.front()->value) < mini){
                mini = check.back()->value - check.front()->value;
                a = check.front()->value;
                b = check.back()->value;
            }

    }
}

int main() {
    int list_num, list_length, tmp, all;
    cin >> list_num;

    vector<element *> array;
    list<element*> checking;
    for (int i = 0; i < list_num; i++) {
        cin >> list_length;
        for (int j = 0; j < list_length; j++) {
            cin >> tmp;
            array.emplace_back(new element(tmp, i));
        }
    }

    sort(array.begin(), array.end(), cmp);

    finding(array, checking, list_num, array.size());
    cout << a << " " << b;


    return 0;
}
