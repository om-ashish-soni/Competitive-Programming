// problem link : https://leetcode.com/contest/weekly-contest-310/problems/divide-intervals-into-minimum-number-of-groups/
// solution : below code

class Solution {
public:
    int minGroups(vector<vector<int>>& intervals) {
        map<int,int> mp;
        vector<pair<int,int>> v;
        for(auto &row:intervals){
            v.push_back({row[0],row[1]});
        }
        
        sort(v.begin(),v.end());
        for(auto &pr:v){
            int left=-pr.first;
            int right=-pr.second;
            auto it=mp.upper_bound(left);
            if(it==mp.end()){
                mp[right]++;
            }else{
                int key=it->first;
                mp[key]--;
                if(mp[key]<=0) mp.erase(key);
                mp[right]++;
            }
        }
        int ctr=0;
        for(auto &pr:mp){
            ctr+=pr.second;
        }
        return ctr;
    }
};
