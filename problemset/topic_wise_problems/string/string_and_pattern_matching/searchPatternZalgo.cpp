// Probem link  : https://practice.geeksforgeeks.org/problems/8dcd25918295847b4ced54055eae35a8501181c1/1
// Solution : below code 

// { Driver Code Starts
#include<bits/stdc++.h>
using namespace std;


 // } Driver Code Ends

class Solution
{
    public:
        void createZ(string& s,int z[]){
            int n=s.size();
            int l,r=0;
            for(int i=1;i<n;i++){
                if(i>r){
                    l=r=i;
                    while(r<n && s[r]==s[r-l]){
                        r++;
                    }
                    z[i]=r-l;
                    r--;
                }else{
                    int k=i-l;
                    if(z[k]<r-i+1){
                        z[i]=z[k];
                    }else{
                        while(r<n && s[r]==s[r-l]){
                            r++;
                        }
                        z[i]=r-l;
                        r--;
                    }
                }
            }
        }
        vector <int> search(string pat, string txt)
        {
            string concat=pat+"$"+txt;
            int psize=pat.size();
            int sz=concat.size();
            int z[sz];
            memset(z,0,sizeof(z));
            createZ(concat,z);
            vector<int> match;
            for(int i=0;i<sz;i++){
                if(z[i]==psize) match.push_back(i-psize);
            }
            return match;
        }
        
     
};
// { Driver Code Starts.
int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        string S, pat;
        cin >> S >> pat;
        Solution ob;
        vector <int> res = ob.search(pat, S);
        if(res.size()==0)
            cout<<"-1 ";
        else
            for (int i : res)
                cout << i << " ";
        cout << endl;
    }
    return 0;
}

  // } Driver Code Ends
