// Problem link : https://www.codechef.com/problems/FAIRELCT
// Problem type : Greedy
#include <bits/stdc++.h>
#define int long long
using namespace std;
void solve(){
    int n,m;
    cin>>n>>m;
    int suma=0,sumb=0;
    priority_queue<int> qb;
    priority_queue<int,vector<int>, greater<int>> qa;
    for(int i=0;i<n;i++){
        int num;
        cin>>num;
        suma+=num;
        qa.push(num);
    }for(int i=0;i<m;i++){
        int num;
        cin>>num;
        sumb+=num;
        qb.push(num);
    }
    if(suma>sumb){
        cout<<0<<endl;
        return;
    }
    int steps=0;
    for(int i=0;i<n;i++){
        int topb=qb.top();
        qb.pop();
        int topa=qa.top();
        qa.pop();
        suma+=topb;
        suma-=topa;
        sumb-=topb;
        sumb+=topa;
        qa.push(topb);
        steps++;
        if(suma>sumb){
            cout<<steps<<endl;
            return;
        }
    }
    if(suma>sumb){
        cout<<steps<<endl;
    }else{
        cout<<-1<<endl;
    }
    return;
}
int32_t main() {
    ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
    
    int test;
    cin>>test;
    while(test--){
        solve();
        
    } 
    
    return 0;
}
