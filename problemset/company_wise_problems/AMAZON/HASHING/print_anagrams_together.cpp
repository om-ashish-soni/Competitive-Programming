// problem link : https://practice.geeksforgeeks.org/problems/print-anagrams-together/1
// solution : below code

// { Driver Code Starts
//Initial Template for C++
#include <bits/stdc++.h>
#include <unordered_map>
using namespace std;


 // } Driver Code Ends
//User function Template for C++

class Solution{
  public:
    vector<vector<string> > Anagrams(vector<string>& string_list) {
        unordered_map<string,int> hash;
        vector<vector<string>> list;
        for(auto &str:string_list){
            string key=str;
            sort(begin(key),end(key));
            if(hash.count(key)==0){
                vector<string> v;
                v.push_back(str);
                list.push_back(v);
                hash[key]=list.size()-1;
            }else{
                int index=hash[key];
                list[index].push_back(str);
            }
        }
        return list;
        //code here
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
        vector<string> string_list(n);
        for (int i = 0; i < n; ++i)
            cin>>string_list[i]; 
        Solution ob;
        vector<vector<string> > result = ob.Anagrams(string_list);
        sort(result.begin(),result.end());
        for (int i = 0; i < result.size(); i++)
        {
            for(int j=0; j < result[i].size(); j++)
            {
                cout<<result[i][j]<<" ";
            }
            cout<<"\n";
        }
    }

    return 0;
}
  // } Driver Code Ends
