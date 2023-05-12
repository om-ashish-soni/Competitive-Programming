// Problem link : https://practice.geeksforgeeks.org/problems/kth-smallest-factor2345/1
// Solution : below code

// { Driver Code Starts
#include <bits/stdc++.h>
using namespace std;

 // } Driver Code Ends
class Solution {
  public:
    int kThSmallestFactor(int N , int K) {
        stack<int> bigFactors;
        int factorsCount=0;
        int sqroot=sqrt(N);
        for(int i=1;i<=sqroot;i++){
            if(N%i == 0){
                factorsCount++;
                if(K==factorsCount) return i;
                if(i != N/i){
                    bigFactors.push(N/i);    
                }
            }
        }
        while(!bigFactors.empty()){
            factorsCount++;
            if(factorsCount==K) return bigFactors.top();
            bigFactors.pop();
        }
        return -1;// kth factor doesn't exist condition
    }
};

// { Driver Code Starts.
int main() {
    int t;
    cin >> t;
    while (t--) {
        int N,K;
        
        cin>>N>>K;

        Solution ob;
        cout << ob.kThSmallestFactor(N,K) << endl;
    }
    return 0;
}  // } Driver Code Ends
