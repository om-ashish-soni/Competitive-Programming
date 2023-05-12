#include <bits/stdc++.h>
#define int long long
using namespace std;

bool ispal(string s){
    string rev=s;
    reverse(rev.begin(),rev.end());
    return s==rev;
}
void yesno(bool b){
    if(b){
        cout<<"Yes"<<endl;
    }else{
        cout<<"No"<<endl;
    }
}
void solve(int t)
{
    int n;
    int a,b;
    cin>>n>>a>>b;
    set<int> s;
    s.insert(a+b);
    s.insert(a-b);
    for(int i=0;i<n;i++){
        int type;
        cin>>type;
        if(type==1){
            cin>>a>>b;
            s.insert(a+b);
            s.insert(a-b);
        }else{
            int x,y;
            cin>>x>>y;
            auto it1=s.lower_bound(x);
            auto it2=s.lower_bound(y);
            int ans=LLONG_MAX;
            if(it1 != it2){
                ans=0;
            }else{
                if(it1 != s.end()){
                    ans=min(ans,abs(*it1-x));
                }
                if(it1 != s.begin()){
                    it1--;
                    ans=min(ans,abs(*it1-x));
                }
                if(it2 != s.end()){
                    ans=min(ans,abs(*it2-y));
                }
                if(it2 != s.begin()){
                    it2--;
                    ans=min(ans,abs(*it2-y));
                }
            }
            cout<<ans<<endl;
        }
    }
    
    

}


signed main()
{
    int t = 1;
    // cin >> t; // testcase
    while (t--)
    {
        solve(t);
    }
    return 0;
}