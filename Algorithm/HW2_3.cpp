#include<iostream>
#include <vector>
#include <set> 
#include <iterator>
#include <string>
#include <algorithm>
using namespace std;

int main()
{
    int cmd_num;
    cin >> cmd_num;

    string cmd;
    vector< set<string> > v_set;
    vector<int> ans;
    while(cmd_num){
        cmd_num--;
        cin >> cmd;
        if( cmd == "PUSH"){
            set<string> temp;
            v_set.push_back(temp);
            ans.push_back(0);
        }
        else if( cmd == "DUP"){
            v_set.push_back(v_set.back());
            ans.push_back(ans.back());
        }
        else if( cmd == "UNION"){
            set<string> temp_y = v_set.back();
            v_set.pop_back();
            set<string> temp_x = v_set.back();
            v_set.pop_back();
            
            set<string> temp_insert;
            set_union(temp_x.begin(), temp_x.end(), temp_y.begin(), temp_y.end(), inserter(temp_insert, temp_insert.begin())); 
            v_set.push_back(temp_insert);
            ans.push_back(temp_insert.size());
        }
        else if( cmd == "INTERSECT"){
            set<string> temp_y = v_set.back();
            v_set.pop_back();
            set<string> temp_x = v_set.back();
            v_set.pop_back();
            
            set<string> temp_insert;
            set_intersection(temp_x.begin(), temp_x.end(), temp_y.begin(), temp_y.end(), inserter(temp_insert, temp_insert.begin())); 
            v_set.push_back(temp_insert);
            ans.push_back(temp_insert.size());
        }
        else{
            

            set<string> temp_y = v_set.back();
            v_set.pop_back();
            set<string> temp_x = v_set.back();
            v_set.pop_back();
            
            
            if(temp_y.size()==0){
                temp_y.insert("{}");
            }

            // string temp_str="{";
            for (std::set<string>::iterator it=temp_x.begin(); it!=temp_x.end(); ++it){
                temp_y.insert(*it) ;
            }
            // temp_str += "}";
            
            // cout << "before insert temp_y=" << endl;
            // for (std::set<string>::iterator it=temp_y.begin(); it!=temp_y.end(); ++it){
            //     cout << *it  << " ,";
            // }
            // cout << "temp_str=" << temp_str << endl;
            
            // temp_y.insert(temp_str);
            // // cout << "after insert temp_y=" << endl;
            // for (std::set<string>::iterator it=temp_y.begin(); it!=temp_y.end(); ++it){
            //     cout << *it  << " ,";
            // }
            v_set.push_back(temp_y);
            ans.push_back(v_set.back().size());
        }
    }

    // Now Component Show
    cout << "{" ;
    for(int i=0; i<v_set.size(); i++){
        cout <<"{" ;
        for (std::set<string>::iterator it=v_set.at(i).begin(); it!=v_set.at(i).end(); ++it){
            std::cout  << *it ;
        }
        cout << "},";
    }
    cout << " }" << endl;


    // Output
    for(int i=0; i<ans.size(); i++){
        cout << ans.at(i) << endl;
    }

    return 0;
}

// INTERSECT

// PUSH
// PUSH
// ADD
// PUSH
// PUSH
// ADD
// ADD
// PUSH
// PUSH
// ADD
// PUSH
// PUSH
// ADD
// PUSH
// ADD
// ADD
// INTERSECT
