// problem link : https://practice.geeksforgeeks.org/problems/largest-subarray-with-0-sum/1/?page=1&company[]=Amazon&curated[]=1&sortBy=submissions#
// solution : below code

// { Driver Code Starts
//Initial Template for C++

#include <bits/stdc++.h>
using namespace std;


 // } Driver Code Ends
/*You are required to complete this function*/

class Solution{
    public:
    int maxLen(vector<int>&arr, int n)
    {   
        // Your code here
        long long sm=0;
        unordered_map<int,int> ump;
        ump[0]=-1;
        int mx=0;
        for(int i=0;i<n;i++){
            sm+=arr[i];
            if(ump.count(sm)){
                int l=ump[sm];
                mx=max(mx,i-l);
            }else{
                ump[sm]=i;
            }
        }
        return mx;
        
    }
};


// { Driver Code Starts.

int main()
{
    int t;
    cin>>t;
    while(t--)
    {
        int m;
        cin>>m;
        vector<int> array1(m);
        for (int i = 0; i < m; ++i){
            cin>>array1[i];
        }
        Solution ob;
        cout<<ob.maxLen(array1,m)<<endl;
    }
    return 0; 
}


  // } Driver Code Ends
