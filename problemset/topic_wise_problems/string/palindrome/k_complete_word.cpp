// problem link : https://codeforces.com/problemset/problem/1332/C
// solution : below code


#include <bits/stdc++.h>
#define int long long
using namespace std;

int getcost(string s, int k)
{
    int n = s.size();
    int half = k / 2;
    int cost = 0;
    vector<int> dp(k,0);
    if(k%2){
        map<char,int> mp;
        for(int i=half;i<n;i+=k){
            mp[s[i]]++;
        }
        int total=0;
        int mx=0;
        for(auto & pr:mp){
            total+=pr.second;
            mx=max(mx,pr.second);
        }
        int delta=total-mx;
        cost+=delta;
    }
    for(int i=0;i<half;i++){
        map<char,int> mp;
        for(int j=0;j<n;j+=k){
            int l=j+i;
            int r=j+k-i-1;
            mp[s[l]]++;
            mp[s[r]]++;
        }
        int total=0;
        int mx=0;
        for(auto & pr:mp){
            total+=pr.second;
            mx=max(mx,pr.second);
        }
        int delta=total-mx;
        cost+=delta;
    }
    return cost;
}
void solve(int t)
{
    int n, k;
    cin >> n >> k;
    string s;
    cin >> s;
    int cost = getcost(s, k);
    cout<<cost<<endl;
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