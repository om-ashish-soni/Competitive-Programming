// problem link : https://practice.geeksforgeeks.org/problems/consecutive-elements2306/1
// solution : below code

//{ Driver Code Starts
#include <bits/stdc++.h> 
using namespace std; 


// } Driver Code Ends
class Solution{
    public:
    string removeConsecutiveCharacter(string s)
    {
        string output;
        output.push_back(s.front());
        for(auto c:s){
            if(output.back() != c) output.push_back(c);
        }
        return output;
    }
};

//{ Driver Code Starts.
int main() 
{ 
    int t;
    cin>>t;
    while(t--)
    {
        string s;
        cin>>s;
        Solution ob;
        cout<<ob.removeConsecutiveCharacter(s)<<endl;
    }
} 




// } Driver Code Ends