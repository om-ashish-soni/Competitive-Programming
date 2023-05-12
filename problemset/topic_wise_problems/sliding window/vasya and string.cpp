// Problem link : https://codeforces.com/problemset/problem/676/C
// Problem type: sliding window 

#include<bits/stdc++.h>
using namespace std;
int main()
{

    int numberoftestcases = 1;
    // cin >> numberoftestcases;
    int t=1;
    while (numberoftestcases--)
    {
        int n,k;
        cin>>n>>k;
        string s;
        cin>>s;
        unordered_map<char,int> hash;
        int l,r;
        l=0;
        r=0;
        hash[s[l]]++;
        int window=1;
        while(r<n){
            // cout<<l<<" "<<r<<" => "<<window<<" __ ";
            if(l>=r){
                // cout<<" case 1"<<endl;
                r++;
                if(r<n){
                    hash[s[r]]++;
                }
            }
            else if(min(hash['a'],hash['b']) > k){
                // cout<<" case 2"<<endl;
                hash[s[l]]--;
                l++;

            }else{
                // cout<<" case 3"<<endl;
                // window=max(window,r-l+1);
                r++;
                if(r<n){
                    hash[s[r]]++;
                }
                if(min(hash['a'],hash['b']) <= k){
                    if(r<n) window=max(window,r-l+1);
                }
            }
        }
        cout<<window<<endl;
    }
    return 0;
}
