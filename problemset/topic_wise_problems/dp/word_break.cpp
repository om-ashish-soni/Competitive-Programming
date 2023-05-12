// problem link  : https://leetcode.com/problems/word-break/
// solution : below code


class Solution {
public:
    map<string,bool> hash;
    bool find(string &s){
        return hash.count(s);
    }
    bool wordBreak(string s, vector<string>& wordDict) {
        for(auto &word:wordDict) hash[word]=true;
        int n=s.size();
        vector<int> dp(n+1,false);
        dp[n]=true;
        for(int i=n-1;i>=0;i--){
            int limit=min(n+1,i+20);
            string key;
            key.push_back(s[i]);
            for(int j=i+1;j<limit;j++){
                if(dp[j]==true and find(key)){
                    dp[i]=true;break;
                }
                key.push_back(s[j]);
            }
        }
        return dp[0];
    }
};
