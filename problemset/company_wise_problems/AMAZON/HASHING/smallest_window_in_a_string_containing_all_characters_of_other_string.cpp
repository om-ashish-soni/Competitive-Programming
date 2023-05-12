// problem link : https://practice.geeksforgeeks.org/problems/smallest-window-in-a-string-containing-all-the-characters-of-another-string-1587115621/1/
// solution : below code

// { Driver Code Starts
#include<bits/stdc++.h>
using namespace std;


 // } Driver Code Ends
class Solution
{
    public:
    //Function to find the smallest window in the string s consisting
    //of all the characters of string p.
    vector<int> uns;
    bool shortlist(vector<queue<int>> &us,vector<int> & up){
        for(char c='a';c<='z';c++){
            if(up[c]>0 && up[c]>us[c].size()) return false;
        }
        return true;
    }
    int getmin(vector<queue<int>> &us,vector<int> & up){
        int mn=INT_MAX;
        for(auto c:uns){
            if(up[c]>us[c].size()) return -1;
            mn=min(mn,us[c].front());
        }
        return mn;
    }
    string smallestWindow (string s, string p)
    {
        vector<int> up(130,0);
        vector<int> checker(130,0);
        vector<queue<int>> us(130);
        for(auto c:p){
            up[c]++;
            
        }
        for(auto c:s) checker[c]++;
        for(char c='a';c<='z';c++){
            if(up[c]>0) uns.push_back(c);
            if(up[c]>checker[c]) return "-1";
        }
        int n=s.size();
        int window_size=n+1;
        int start=-1,end=-1;
        for(int i=0;i<n;i++){
            if(up[s[i]]>0){
                if(us[s[i]].size()>=up[s[i]]){
                    us[s[i]].pop();
                }
                us[s[i]].push(i);
                
                int mn=getmin(us,up);
                if(mn != -1){
                    if(window_size>i-mn+1){
                        window_size=i-mn+1;
                        start=mn;
                        end=i;
                    }
                }
            }
                
        }
        // cout<<start<<" "<<end<<endl;
        if(start!=-1 && end != -1) return s.substr(start,window_size);
        return  "-1";
        // Your code here
    }
};

// { Driver Code Starts.
int main()
 {
    int t;
    cin>>t;
    while(t--)
    {
        string s;
        cin>>s;
        string pat;
        cin>>pat;
        Solution obj;
        cout<<obj.smallestWindow(s, pat)<<endl;
        
    }
	return 0;
}  // } Driver Code Ends
