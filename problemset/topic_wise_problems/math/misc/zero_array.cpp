// problem link : https://codeforces.com/problemset/problem/1201/B
// solution : below code

#include <bits/stdc++.h>
#define int long long
using namespace std;


void solve(int t)
{
    int n;
    cin>>n;
    vector<int> v(n);
    for(int i=0;i<n;i++) cin>>v[i];
    long long sm=accumulate(v.begin(),v.end(),0LL);
    long long mx=*max_element(v.begin(),v.end());
    if(mx*2 > sm) cout<<"NO";
    else if(sm&1) cout<<"NO";
    else cout<<"YES";
    cout<<endl;

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