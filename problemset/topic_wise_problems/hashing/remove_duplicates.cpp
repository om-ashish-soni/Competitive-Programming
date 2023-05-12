// problem link : https://practice.geeksforgeeks.org/problems/remove-all-duplicates-from-a-given-string4321/1
// solution : below code

//{ Driver Code Starts
#include <bits/stdc++.h>

using namespace std;


// } Driver Code Ends
//User function template for C++
class Solution{
public:
    
	string removeDuplicates(string str) {
	    string trimmed;
	    unordered_map<char,bool> hashmap;
	    hashmap.reserve(60);
	    for(auto c:str){
	        if(hashmap.count(c)==0){
	            hashmap[c]=true;
	            trimmed.push_back(c);
	        }
	    }
	    return trimmed;
	    
	}
};

//{ Driver Code Starts.

int main() {
    int t;
    cin >> t;
    while (t--) {
        string str;
        cin >> str;
        Solution ob;
        auto ans = ob.removeDuplicates(str);

        cout << ans << "\n";
    }
    return 0;
}
// } Driver Code Ends