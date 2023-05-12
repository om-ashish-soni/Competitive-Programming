// problem link : https://leetcode.com/problems/merge-intervals/
// solution : below code

class Solution {
public:
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        vector<pair<int,int>> v;
        for(auto &range:intervals) v.push_back({range[0],range[1]});
        sort(v.begin(),v.end());
        vector<pair<int,int>> merged;
        merged.push_back(v[0]);
        for(auto &curr:v){
            pair<int,int> &prev=merged.back();
            if(prev.second>=curr.first ){
                if(prev.second<curr.second) prev.second=curr.second;
            }else{
                merged.push_back(curr);
            }
        }
        vector<vector<int>> output;
        for(auto &pr:merged) output.push_back(vector<int>{pr.first,pr.second});
        return output;
    }
};
