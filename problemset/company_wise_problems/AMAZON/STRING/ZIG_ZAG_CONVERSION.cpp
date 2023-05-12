// problem link : https://leetcode.com/problems/zigzag-conversion/
// solution : below code

class Solution {
public:
    string convert(string s, int numRows) {
        if(numRows==1) return s;
        string z;
        vector<string> v(numRows);
        int n=numRows;
        int places=2*n - 2 ;
        for(int i=0;i<s.size();i++){
            int mod=i%places;
            if(mod<n) v[mod]+=s[i];
            else{
                int diff=mod-n+1;
                int index=n-diff-1;
                v[index]+=s[i];
            }
        }
        for(auto &str:v){
            z+=str;
        }
        return z;
    }
};
