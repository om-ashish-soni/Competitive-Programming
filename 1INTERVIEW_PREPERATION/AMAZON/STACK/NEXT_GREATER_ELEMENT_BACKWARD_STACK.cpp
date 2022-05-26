// problem link : https://practice.geeksforgeeks.org/problems/next-larger-element-1587115620/1/
// solution : below code

// { Driver Code Starts
#include<bits/stdc++.h>
using namespace std;


 // } Driver Code Ends
class Solution
{
    public:
    //Function to find the next greater element for each element of the array.
    vector<long long> nextLargerElement(vector<long long> arr, int n){
        vector<long long > v(n,-1);
        stack<long long> stk;
    
        for(int i=n-1;i>=0;i--){
            while(stk.size()>0){
                long long top=stk.top();
                if(arr[i]<top){
                    v[i]=top;
                    break;
                }
                stk.pop();
            }
            stk.push(arr[i]);
        }
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
        cin>>n;
        vector<long long> arr(n);
        for(int i=0;i<n;i++)
            cin>>arr[i];
        
        Solution obj;
        vector <long long> res = obj.nextLargerElement(arr, n);
        for (long long i : res) cout << i << " ";
        cout<<endl;
    }
	return 0;
}  // } Driver Code Ends
