// Problem link : https://practice.geeksforgeeks.org/problems/least-prime-factor5216/1
// Solution : below code

// { Driver Code Starts
#include<bits/stdc++.h> 
using namespace std;

 // } Driver Code Ends
class Solution{
public: 
    
    long long int largestPrimeFactor(int N){
        int largestPrimeFactorOfN = 1;
        int sqroot=sqrt(N);
        for(int i=2;i<=sqroot;i++){
            if(N<2) break;
            if(N%i==0){
                largestPrimeFactorOfN=i;
                while(N%i==0){
                    N /= i;
                }
            }
        }
        if(N>1) largestPrimeFactorOfN=N;
        return largestPrimeFactorOfN;
    }
};

// { Driver Code Starts.
int main() 
{ 
    int t;
    cin>>t;
    while(t--)
    {
        int N;
        cin>>N;
        Solution ob;
        cout << ob.largestPrimeFactor(N) << endl;
    }
    return 0; 
}  // } Driver Code Ends
