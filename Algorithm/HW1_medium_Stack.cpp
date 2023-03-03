#include<iostream>
#include <vector>
#include <stack>
#include <set> 
#include <map>
#include <string>
#include <algorithm>
// #include <stdbool.h>
using namespace std;

// int FindIt(map< set<int>, int > mp, set<int> st);

int main()
{
    int cmd_num;
    cin >> cmd_num;

    vector<int> ans;
    stack<int> st;
    map< set<int>, int > mp;
    map< int, set<int> > mp2;
    set<int> temp_s;
    string cmd;
    int numbers = 0;
    mp.insert( pair< set<int>, int > ( temp_s, numbers ));
    mp2.insert( pair< int, set<int> > ( numbers, temp_s ));
    numbers++;

    while(cmd_num){
        cmd_num--;
        cin >> cmd;
        if( cmd == "PUSH"){
            st.push(0);
            ans.push_back(0);
        }
        else if( cmd == "DUP"){
            st.push(st.top());
            ans.push_back(ans.back());
        }
        else if( cmd == "ADD"){ //先出棧的集合加入後出棧的集合中
            map< int, set<int> > ::iterator it; //先出棧的集合
            it = mp2.find(st.top()); 
            st.pop();
            map< int, set<int> > ::iterator it2; //後出棧的集合
            it2 = mp2.find(st.top()); 
            st.pop();
            set<int> st_new = it2->second;   //新集合
            
            //先出棧的集合+{}
            set<int> st_first;  
            st_first.insert(it->first); 
            map< set<int>, int > ::iterator it_find;
            it_find = mp.find(st_first); 
            if(it_find == mp.end()){
                mp.insert(pair< set<int>, int > ( st_first,  numbers));
                mp2.insert( pair< int, set<int> > ( numbers, st_first ));
                st_new.insert(numbers); 
                numbers++;
            }
            else {
                st_new.insert(it_find->second);
            }
            
            //ADD後的集合
            map< set<int>, int > ::iterator it_find_new;
            it_find_new = mp.find(st_new); 
            if(it_find_new == mp.end()){
                mp.insert(pair< set<int>, int > ( st_new, numbers ));
                mp2.insert( pair< int, set<int> > ( numbers, st_new ));
                st.push(numbers);
                numbers++;
            }
            else {
                st.push(it_find_new->second);
            }
            ans.push_back(st_new.size());
        }
        else if( cmd == "INTERSECT" ){
            map< int, set<int> > ::iterator it; //先出棧的集合
            it = mp2.find(st.top()); 
            st.pop();
            map< int, set<int> > ::iterator it2; //後出棧的集合
            it2 = mp2.find(st.top()); 
            st.pop();

            set<int> temp_x = it->second;
            set<int> temp_y = it2->second;
            set<int> temp_insert;
            set_intersection(temp_x.begin(), temp_x.end(), temp_y.begin(), temp_y.end(), inserter(temp_insert, temp_insert.begin())); 
            map< set<int>, int > ::iterator it_find;
            it_find = mp.find(temp_insert); 
            if(it_find == mp.end()){
                mp.insert(pair< set<int>, int > ( temp_insert,  numbers));
                mp2.insert( pair< int, set<int> > ( numbers, temp_insert ));
                st.push(numbers); 
                numbers++;
            }
            else {
                st.push(it_find->second);
            }
            ans.push_back(temp_insert.size());
        }
        else{
            map< int, set<int> > ::iterator it; //先出棧的集合
            it = mp2.find(st.top()); 
            st.pop();
            map< int, set<int> > ::iterator it2; //後出棧的集合
            it2 = mp2.find(st.top()); 
            st.pop();

            set<int> temp_x = it->second;
            set<int> temp_y = it2->second;
            set<int> temp_union;
            set_union(temp_x.begin(), temp_x.end(), temp_y.begin(), temp_y.end(), inserter(temp_union, temp_union.begin())); 
            map< set<int>, int > ::iterator it_find;
            it_find = mp.find(temp_union); 
            if(it_find == mp.end()){
                mp.insert(pair< set<int>, int > ( temp_union,  numbers));
                mp2.insert( pair< int, set<int> > ( numbers, temp_union ));
                st.push(numbers); 
                numbers++;
            }
            else {
                st.push(it_find->second);
            }
            ans.push_back(temp_union.size());
        }
    }

    // Output
    for(int i=0; i<ans.size(); i++){
        cout << ans.at(i) << endl;
    }

    return 0;

}

// int FindIt(map< set<int>, int > mp, set<int> st){
//     map< set<int>, int > ::iterator it_find;
//     it_find = mp.find(st); 
//     if(it_find == mp.end()){
//         return -1;
//     }
//     return it_find->second;
// }