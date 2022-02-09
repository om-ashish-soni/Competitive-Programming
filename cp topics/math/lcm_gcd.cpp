// Problem link : https://practice.geeksforgeeks.org/problems/lcm-and-gcd4516/1
// Solution : below code

// { Driver Code Starts
#include <bits/stdc++.h>
using namespace std;

 // } Driver Code Ends
class Solution {
  public:
    long long gcd(long long a,long long b){
        if(b==0) return a;
        return gcd(b,a%b);
    }
    long long lcm(long long a,long long b){
        return (a/gcd(a,b))*b;
    }
    vector<long long> lcmAndGcd(long long a , long long b) {
        vector<long long> lcm_gcd_pair(2,-1);
        lcm_gcd_pair[1]=gcd(a,b);
        lcm_gcd_pair[0]=lcm(a,b);
        return lcm_gcd_pair;
    }
};

// { Driver Code Starts.
int main() {
    int t;
    cin >> t;
    while (t--) {
        long long A,B;
        
        cin>>A>>B;

        Solution ob;
        vector<long long> ans = ob.lcmAndGcd(A,B);
        cout<<ans[0]<<" "<<ans[1]<<endl;
    }
    return 0;
}  // } Driver Code Ends
