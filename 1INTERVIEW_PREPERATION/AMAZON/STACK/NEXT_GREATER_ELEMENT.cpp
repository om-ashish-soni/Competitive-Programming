// problem link : https://www.geeksforgeeks.org/next-greater-element/
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
        priority_queue<pair<long long,long long>> pq;
        pq.push({-arr[0],0});
        for(int i=1;i<n;i++){
            long long val=-arr[i];
            while(pq.size()>0 and pq.top().first>val){
                int pos=pq.top().second;
                arr[pos]=-val;
                pq.pop();
            }
            pq.push({val,i});
        }
        while(pq.size()>0){
            int pos=pq.top().second;
            arr[pos]=-1;
            pq.pop();
        }
        return arr;
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
