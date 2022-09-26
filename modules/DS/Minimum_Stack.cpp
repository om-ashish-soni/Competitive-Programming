#include<bits/stdc++.h>
using namespace std;
template<typename T>class MinStack{
    stack<pair<T,T>> stk;
    public:
    void push(T elem){
        if(stk.size()==0){
            stk.push({elem,elem});
        }else{
            stk.push({elem,min(elem,stk.top().second)});
        }
    }
    T pop(){
        T elem=stk.top().first;
        stk.pop();
        return elem;
    }
    T getMin(){
        if(stk.size()==0) throw "-1";
        return stk.top().second;
    }
};
void solve(){
    MinStack<int> stk=*new MinStack<int>();
    stk.push(1);
    cout<<stk.getMin()<<endl;
    stk.push(2);
    cout<<stk.getMin()<<endl;
    stk.push(0);
    cout<<stk.getMin()<<endl;
}
signed main(){
    solve();
    return 0;
}
