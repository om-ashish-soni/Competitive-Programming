// problem link : https://codeforces.com/contest/1780/problem/B
// solution : below code

#include <bits/stdc++.h>
#define int long long
using namespace std;


void solve(int t)
{
    int n;
    cin>>n;
    vector<int> v(n);
    for(int i =0;i<n;i++) cin>>v[i];
    int sum=accumulate(v.begin(),v.end(),0LL);
    int left=0;
    int mx=0;
    for(int i=0;i<n-1;i++){
        left+=v[i];
        int right=sum-left;
        int ctr=__gcd(left,right);
        mx=max(mx,ctr);
    }
    cout<<mx<<endl;
}

signed main()
{
    int t = 1;
    cin >> t; // testcase
    while (t--)
    {
        solve(t);
    }
    return 0;
}