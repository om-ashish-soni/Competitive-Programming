// problem link : https://practice.geeksforgeeks.org/problems/maximum-repeating-number4858/1
// solution : below code
//{ Driver Code Starts
#include <bits/stdc++.h>

using namespace std;


// } Driver Code Ends
//User function template for C++
class Solution{
public:	
	// Returns maximum repeating element in arr[0..n-1].
	// The array elements are in range from 0 to k-1
    int maxRepeating(int *arr, int n, int k) {
	    vector<int> hash(k+1,0);
        for(int i=0;i<n;i++){
            hash[arr[i]]++;
        }
        int maxRepeating=0;
        for(int i=1;i<=k;i++){
            if(hash[i]>hash[maxRepeating]){
                maxRepeating=i;
            }
        }
        return maxRepeating;
	}
};

//{ Driver Code Starts.

int main() {
    int t;
    cin >> t;
    while (t--) {
        int n, k;
        cin >> n >> k;
        int arr[n];
        for (int i = 0; i < n; i++) {
            cin >> arr[i];
        }
        Solution ob;
        auto ans = ob.maxRepeating(arr, n, k);
        cout << ans << "\n";
    }
    return 0;
}

// } Driver Code Ends