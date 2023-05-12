// problem link : https://leetcode.com/problems/ones-and-zeroes/
// solution : below code

class Solution {
public:
    int findMaxForm(vector<string>& strs, int m, int n) {
        int sz=strs.size();
        vector<pair<int,int>> v(sz);
        for(int i=0;i<sz;i++){
            int z=count(begin(strs[i]),end(strs[i]),'0');
            v[i].first=z;
            v[i].second=strs[i].size()-z;
        }
        vector<vector<int>> dp(m+1,vector<int>(n+1,0));
        for(int i=0;i<sz;i++){
            int fi=v[i].first;
            int se=v[i].second;
            if(fi<=m && se<=n){
                map<pair<int,int>,int> hash;
                if(dp[fi][se]<1) hash[{fi,se}]=1;
                for(int mi=0;mi<=m;mi++){
                    for(int nj=0;nj<=n;nj++){
                        if(dp[mi][nj]>0 && mi+fi<=m && nj+se<=n){
                            if(dp[mi+fi][nj+se]<1+dp[mi][nj]) hash[{mi+fi,nj+se}]=1+dp[mi][nj];
                        }
                    }
                }
                for(auto &pr:hash){
                    dp[pr.first.first][pr.first.second]=pr.second;
                }
            }
        }
        int ctr=0;
        for(int i=0;i<=m;i++){
            for(int j=0;j<=n;j++){
                ctr=max(ctr,dp[i][j]);
            }
        }
        return ctr;
    }
};
