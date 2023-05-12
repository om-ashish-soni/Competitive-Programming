// problem link : https://practice.geeksforgeeks.org/problems/equilibrium-point-1587115620/1/?page=1&company[]=Amazon&curated[]=1&sortBy=submissions#
// solution : below code

// { Driver Code Starts
#include <iostream>
using namespace std;


 // } Driver Code Ends
class Solution{

    public:
    // Function to find equilibrium point in the array.
    // a: input array
    // n: size of array
    int equilibriumPoint(long long a[], int n) {
        if(n==1) return 1;
        int pref[n],suff[n];
        pref[0]=a[0];
        suff[n-1]=a[n-1];
        for(int i=1;i<n;i++) pref[i]=pref[i-1]+a[i];
        for(int i=n-2;i>=0;i--) suff[i]=suff[i+1]+a[i];
        if(suff[1]==0) return 1;
        for(int i=1;i<n-1;i++){
            if(pref[i-1]==suff[i+1]) return i+1;   
        }
        if(pref[n-2]==0) return n;
        return -1;
        // Your code here
    }

};

// { Driver Code Starts.


int main() {

    long long t;
    
    //taking testcases
    cin >> t;

    while (t--) {
        long long n;
        
        //taking input n
        cin >> n;
        long long a[n];

        //adding elements to the array
        for (long long i = 0; i < n; i++) {
            cin >> a[i];
        }
        
        Solution ob;

        //calling equilibriumPoint() function
        cout << ob.equilibriumPoint(a, n) << endl;
    }
    return 0;
}
  // } Driver Code Ends
