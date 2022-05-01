// problem link : https://www.codechef.com/problems/RED1
// solution : below codee
#include <bits/stdc++.h>
#define int long long
using namespace std;
void scan(int *arr,int n){
    for(int i=0;i<n;i++) cin>>arr[i];
}
void solve(int t=0){
    int n;cin>>n;
    int ans=-1;
    int sqroot=sqrt(n);
    if(n==1){
        ans=0;
    }else if(n%2==1){
        ans=1;
    }else if(sqroot*sqroot==n){
        ans=1;
    }else{
        int twos=0;
        while(n>1 and n%2==0){
            n/=2;
            twos++;
        }
        // cout<<"twos : "<<twos<<endl;
        if(twos%2==1){
            ans=-1;
        }else{
            ans=2;
        }
    }
    cout<<ans<<endl;
    
}
signed main() {

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
#ifndef ONLINE_JUDGE 
    freopen("input.txt", "r", stdin);
    freopen("error.txt", "w", stderr);
    freopen("output.txt", "w", stdout);
#endif
    int t;cin>>t;
    while(t--){
        solve();    
    }
    return 0;
}
