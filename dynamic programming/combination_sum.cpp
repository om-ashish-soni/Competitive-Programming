// problem link : https://leetcode.com/problems/combination-sum/
// solution : below code

class Solution {
public:
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        sort(candidates.begin(),candidates.end());
        vector<vector<int>>* dp[target+1];
        for(int i=0;i<=target;i++){
            dp[i]=new vector<vector<int>>;   
        }
        (*dp[0]).push_back({});
        for(int i=0;i<=target;i++){
            for(auto num:candidates){
                
                if(i+num>target) break;
                for(auto& row:*dp[i]){
                    if(row.size()>0 && row[row.size()-1]<num) continue; 
                    vector<vector<int>>& table=*dp[i+num];
                    table.push_back(row);
                    table[table.size()-1].push_back(num);
                }
            }
        }
        return *dp[target];
    }
};
