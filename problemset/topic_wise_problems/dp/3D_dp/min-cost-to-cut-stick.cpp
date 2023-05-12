// problem link : https://leetcode.com/problems/minimum-cost-to-cut-a-stick/description/
// solution : below code

class Solution {
public:
    
    int minCost(int n, vector<int>& cuts) {
        cuts.push_back(0);
        cuts.push_back(n);
        sort(cuts.begin(),cuts.end());
        int sz=cuts.size();
        vector<vector<long long>> dp(sz,vector<long long>(sz,INT_MAX));
        for(int d=1;d<sz;d++){
            for(int i=0;i<sz-d;i++){
                int j=i+d;
                long long my_cost=INT_MAX;
                bool isThereAnyOne=false;
                for(int k=i+1;k<j;k++){
                    isThereAnyOne=true;
                    long long curr_cost=dp[i][k]+dp[k][j];
                    my_cost=min(my_cost,curr_cost);
                }
                if(isThereAnyOne==false){
                    my_cost=0;
                }
                long long len=cuts[j]-cuts[i];
                my_cost+=len;
                dp[i][j]=min(dp[i][j],my_cost);
                // cout<<"dp["<<cuts[i]<<","<<cuts[j]<<"] : "<<dp[i][j]<<endl;
            }
        }
        return dp[0][sz-1]-n;
    }
};