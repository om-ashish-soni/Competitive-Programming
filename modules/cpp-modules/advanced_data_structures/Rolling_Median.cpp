#include<bits/stdc++.h>
using namespace std;

#define ll long long 

//TC - nlogn
//get a Median in each subarray 
struct Rolling_Median{

    multiset<ll>left,right;
    ll sum_left,sum_right;

    Rolling_Median(){
        sum_left=0;
        sum_right=0;
    }

    void handle_change(){
        int szl=left.size();
        int szr=right.size();

        if((szl==0 && szr==0) || (szl==1 && szr==0)){
            return;
        }

        if(szl==0 && szr>0){
            ll right_element=*right.begin();

            sum_right-=right_element;
            right.erase(right.find(right_element));
            sum_left+=right_element;
            left.insert(right_element);
            return;
        }

        if(szl>szr){
            ll left_element=*left.rbegin();

            sum_left-=left_element;
            left.erase(left.find(left_element));
            sum_right+=left_element;
            right.insert(left_element);
        }
        else if(szl+1<szr){
            ll right_element=*right.begin();

            sum_right-=right_element;
            right.erase(right.find(right_element));
            sum_left+=right_element;
            left.insert(right_element);
        }

        ll right_element=*right.begin();
        ll left_element=*left.rbegin();

        if(left_element>right_element){
            sum_left-=left_element;
            left.erase(left.find(left_element));
            sum_left+=right_element;
            left.insert(right_element);
            sum_right+=left_element;
            right.insert(left_element);
            sum_right-=right_element;
            right.erase(right.find(right_element));
        }

    }

    void insert(ll num){

        if(left.empty()){
            left.insert(num);
            sum_left+=num;
            return;
        }
        left.insert(num);
        handle_change();
    }

    void remove(ll num){
        auto it=left.find(num);
        if(it!=left.end()){
            
            left.erase(it);
            sum_left-=num;
            handle_change();
        }
        else{
            it=right.find(num);

            if(it!=right.end()){
                right.erase(it);
                sum_right-=num;
                handle_change();
            }
        }
    }

    pair<ll,ll> get_Median(){
        int left_element=*left.rbegin();
        int right_element=*right.begin();
        return {left_element,right_element};
    }
};


