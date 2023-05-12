// Problem Link : https://www.codechef.com/problems/CIELRCPT
// Problem type: greedy
#include <bits/stdc++.h>
#define ll long long
using namespace std;
int countSetBits(long &num){
    long setBits=0;
    int multi=2048;
    while(num){
        setBits+=num/multi;
        num=num%multi;
        multi>>=1;
    }
    return setBits;
}
int32_t main() {
    ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
    
    int test;
    cin>>test;
    while(test--){
        
        long num;
        cin>>num;
        cout<<countSetBits(num)<<endl;
    } 
    
    return 0;
}
