// Problem link : https://practice.geeksforgeeks.org/problems/factors-sum2016/1
// Solution : below code

// { Driver Code Starts
#include <bits/stdc++.h>
using namespace std;

 // } Driver Code Ends
class Solution
{
	public:
    long long factorSum(int N)
    {
        long long sumOfAllFactors=0;
        long long sqroot=sqrt(N);
        for(long long i=1;i<=sqroot;i++){
            if(N%i==0){
                sumOfAllFactors+=i;
                if(i != N/i){
                    sumOfAllFactors+=N/i;
                }
            }
        }
        return sumOfAllFactors;
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
        cin >> N;

        Solution ob;
       	cout <<  ob.factorSum(N) << "\n";
   
    }
    return 0;
}
  // } Driver Code Ends
