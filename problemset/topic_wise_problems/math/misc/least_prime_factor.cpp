// Problem link : https://practice.geeksforgeeks.org/problems/least-prime-factor5216/1
// Solution : 

// { Driver Code Starts
// Initial Template for C++
#include <bits/stdc++.h>
using namespace std;

 // } Driver Code Ends
// User function Template for C++
const int sizeOfBitset=1e3 + 10;
bitset<sizeOfBitset> isNotPrime;
class Solution {
  public:
    
    
    
    vector<int> leastPrimeFactor(int n) {
        vector<int> lowestPrimeFactorOf(n+1,-1);
        isNotPrime[0]=isNotPrime[1]=1;
        lowestPrimeFactorOf[1]=1;
        for(int i=2;i<=n;i++){
            if(!isNotPrime[i]){
                lowestPrimeFactorOf[i]=i;
                for(int j=i*i;j<=n;j+=i){
                    isNotPrime[j]=1;
                    if(-1 == lowestPrimeFactorOf[j]){
                        lowestPrimeFactorOf[j]=i;
                    }
                }
            }
        }
        return lowestPrimeFactorOf;
        // code here
    }
};

// { Driver Code Starts.
int main() {
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        Solution ob;
        vector<int>ans = ob.leastPrimeFactor(n);
        for(int i=1;i<=n;i++)cout<<ans[i]<<" ";
        cout<<endl;  
    }
    return 0;
}
  // } Driver Code Ends
