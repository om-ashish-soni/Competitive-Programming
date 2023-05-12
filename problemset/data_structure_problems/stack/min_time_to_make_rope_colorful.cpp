// problem link : https://leetcode.com/problems/minimum-time-to-make-rope-colorful/description/
// solution : below code

class Solution {
public:
    int minCost(string s, vector<int>& cost) {
        int n=s.size();
        vector<pair<char,pair<int,int>>> v;
        int i=0;
        for(auto c:s){
            if(v.size()==0 || v.back().first != c){
                v.push_back({c,{cost[i],cost[i]}});
            }else{
                v.back().second.first=max(v.back().second.first,cost[i]);
                v.back().second.second+=cost[i];
            }
            i++;
        }
        long long sm=0;
        for(auto & pr:v){
            sm+=pr.second.second-pr.second.first;
        }
        return sm;
    }
};