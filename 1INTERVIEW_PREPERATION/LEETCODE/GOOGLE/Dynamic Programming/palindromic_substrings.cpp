// problem link : https://leetcode.com/problems/palindromic-substrings/
// solution : below code
#define vb vector<bool>
#define vvb vector<vb>
class Solution {
public:
    bool ispal(string &s,vvb & dp,int i,int j){
        if(i+1>=j-1 || dp[i+1][j-1]) return s[i]==s[j];
        return false;
    }
    int countSubstrings(string s) {
        int n=s.size();
        vvb dp(n,vb(n,false));
        int ctr=n;
        for(int i=0;i<n;i++) dp[i][i]=true;
        for(int i=0;i<n;i++){
            for(int j=0;j<n-i-1;j++){
                dp[j][j+i+1]=ispal(s,dp,j,j+i+1);
                if(dp[j][j+i+1]) ctr++;
            }
        }
        return ctr;
    }
};
