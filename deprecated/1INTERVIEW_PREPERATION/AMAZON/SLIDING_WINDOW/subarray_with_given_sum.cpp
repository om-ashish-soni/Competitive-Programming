// problem link : https://practice.geeksforgeeks.org/problems/subarray-with-given-sum-1587115621/1/?page=1&company[]=Amazon&sortBy=submissions#
// solution : below code

// { Driver Code Starts
#include <bits/stdc++.h>
using namespace std;


 // } Driver Code Ends
class Solution
{
    public:
    //Function to find a continuous sub-array which adds up to a given number.
    vector<int> subarraySum(int arr[], int n, long long s)
    {
        int l=0,r=0;
        int sm=0;
        while(r<n){
            sm+=arr[r];
            while(sm>s && l<r){
                sm-=arr[l];
                l++;
            }
            if(sm==s) break;
            r++;
        }
        vector<int> rejected{-1};
        if(sm!=s) return rejected;
        vector<int> v{l+1,r+1};
        return v;
    }
};

// { Driver Code Starts.

int main()
 {
    int t;
    cin>>t;
    while(t--)
    {
        int n;
        long long s;
        cin>>n>>s;
        int arr[n];
        const int mx = 1e9;
        for(int i=0;i<n;i++)
        {
            cin>>arr[i];
        }
        Solution ob;
        vector<int>res;
        res = ob.subarraySum(arr, n, s);
        
        for(int i = 0;i<res.size();i++)
            cout<<res[i]<<" ";
        cout<<endl;
        
    }
	return 0;
}  // } Driver Code Ends
