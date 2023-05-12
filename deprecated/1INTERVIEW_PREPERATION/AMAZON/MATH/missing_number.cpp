// problem link : https://practice.geeksforgeeks.org/problems/missing-number-in-array1416/1/?page=1&company[]=Amazon&curated[]=1&sortBy=submissions#
// solution : below code

// { Driver Code Starts
// Initial template for C++

#include <bits/stdc++.h>
using namespace std;




 // } Driver Code Ends
// User function template for C++

class Solution{
  public:
    int MissingNumber(vector<int>& array, int n) {
        // Your code goes here
        long long N=n;
        long long sm=0;
        for(auto num:array) sm+=num;
        long long ideal=(N*(N+1))/2;
        return ideal-sm;
    }
};

// { Driver Code Starts.

int main() {
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;

        vector<int> array(n - 1);
        for (int i = 0; i < n - 1; ++i) cin >> array[i];
        Solution obj;
        cout << obj.MissingNumber(array, n) << "\n";
    }
    return 0;
}  // } Driver Code Ends
