// problem link : https://practice.geeksforgeeks.org/problems/convert-array-into-zig-zag-fashion1638/1/?page=1&company[]=Amazon&curated[]=1&sortBy=submissions#
// solution : below code

// { Driver Code Starts
#include <bits/stdc++.h>

using namespace std;


 // } Driver Code Ends
//User function template for C++
class Solution{
public:	
	// Program for zig-zag conversion of array
	void zigZag(int arr[], int n) {
	    for(int i=0;i<n;i+=2){
	       // cout<<arr[i]<<" ; "<<i+1<<" , "<<i+2<<endl;
	        int limit=min(i+3,n);
	        if(i+1<n){
	            if(arr[i]>arr[i+1]) swap(arr[i],arr[i+1]);
	            if(i+2<n){
	                if(arr[i+1]<arr[i+2]) swap(arr[i+1],arr[i+2]);
	            }
	        }
	       // for(int j=0;j<n;j++) cout<<arr[j]<<" ";cout<<endl;
	    }
	    
	}
};

// { Driver Code Starts.

int main() {
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        int arr[n];
        for (int i = 0; i < n; i++) {
            cin >> arr[i];
        }
        Solution ob;
        ob.zigZag(arr, n);
        for (int i = 0; i < n; i++) {
            cout << arr[i] << " ";
        }
        cout << "\n";
    }
    return 0;
}
  // } Driver Code Ends
