// problem link : https://leetcode.com/problems/word-break-ii/
// solution : below code

class Solution {
public:
    map<string,bool> hash;
    bool find(string &s){
        return hash.count(s);
    }
    void appendVector(vector<int>& v,vector<int>& w){
        v.insert(v.end(),w.begin(),w.end());
    }
    vector<string> wordBreak(string s, vector<string>& wordDict) {
        for(auto &word:wordDict) hash[word]=true;
        int n=s.size();
        vector<vector<string>> dp(n+1);
        dp[n].push_back("");
        for(int i=n-1;i>=0;i--){
            int limit=min(n+1,i+10);
            string key;
            key.push_back(s[i]);
            for(int j=i+1;j<limit;j++){
                if(dp[j].size()>0 and find(key)){
                    for(auto &str:dp[j]){
                        if(str.size()>0) dp[i].push_back(key+" "+str);
                        else dp[i].push_back(key);
                    }
                }
                key.push_back(s[j]);
            }
        }
        return dp[0];
    }
};
