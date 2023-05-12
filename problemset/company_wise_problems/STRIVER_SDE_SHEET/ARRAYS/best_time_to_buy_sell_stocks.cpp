// problem link : https://leetcode.com/problems/best-time-to-buy-and-sell-stock/
// solution : below code

class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int mx=0;
        int profit=0;
        int n=prices.size();
        for(int i=n-1;i>=0;i--){
            profit=max(profit,mx-prices[i]);
            mx=max(mx,prices[i]);
        }
        return profit;
    }
};
