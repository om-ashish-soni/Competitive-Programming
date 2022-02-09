// Problem link : https://practice.geeksforgeeks.org/problems/sieve-of-eratosthenes5242/1
// Solution : below code

// { Driver Code Starts
#include<bits/stdc++.h> 
using namespace std; 

 // } Driver Code Ends
//User function Template for C++


class Solution
{
public:
    vector<int> sieveOfEratosthenes(int n)
    {   
        const int sizeOfBitset=1e4 + 10;
        bitset<sizeOfBitset> isNotPrime;
        isNotPrime[0]=isNotPrime[1]=1;
        vector<int> primes;
        for(int i=2;i<=n;i++){
            if(0==isNotPrime[i]){
                primes.push_back(i);
                for(int j=i*i;j<=n;j+=i){
                    isNotPrime[j]=1;
                }
            }
        }
        return primes;
        // Write Your Code here
    }
};

// { Driver Code Starts.
int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        int N;
        cin>>N;
        Solution ob;
        vector<int> primes  = ob.sieveOfEratosthenes(N);
        for(auto prime : primes) {
            cout<< prime <<" ";
        }
        cout<<endl;
    }
    return 0;
}  // } Driver Code Ends
