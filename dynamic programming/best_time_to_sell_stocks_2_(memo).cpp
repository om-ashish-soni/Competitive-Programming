class Solution {
public:
    int maxProfit(vector<int> &prices,vector<int> &memo,int i=0){
        if(i>=prices.size()) return 0;
        if(-1 != memo[i]) return memo[i];
        int profit=0;
        if(i<prices.size()-1){
            int temp=maxProfit(prices,memo,i+1);
            if(prices[i+1]-prices[i]>=0) profit=max(profit,prices[i+1]-prices[i]+temp);
            else profit=max(profit,temp);
        }
        memo[i]=profit;
        return memo[i];
    }
    int maxProfit(vector<int>& prices) {
        vector<int> memo(prices.size(),-1);
        int mx=0;
        mx=maxProfit(prices,memo);
        return mx;
    }
};