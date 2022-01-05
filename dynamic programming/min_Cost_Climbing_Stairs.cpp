class Solution {
public:
    int minCostClimbingStairs(vector<int>& cost) {
        vector<int> costs;
        costs.push_back(0);
        for(auto money:cost) costs.push_back(money);
        costs.push_back(0);
        vector<int> v(costs.size(),INT_MAX);
        v[0]=0;
        for(int i=0;i<costs.size();i++){
            if(i+1<costs.size()) v[i+1]=min(v[i+1],v[i]+costs[i+1]);
            if(i+2<costs.size()) v[i+2]=min(v[i+2],v[i]+costs[i+2]);
        }
        int ans;
        for(auto money:v) {ans=money;}
        return ans;
    }
};