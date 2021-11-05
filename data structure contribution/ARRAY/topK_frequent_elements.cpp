class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        unordered_map<int,int> ump;
        set<pair<int,int>> s;
        stack<int> stk;
        vector<int> v;
        for(auto num:nums) ump[num]++;
        for(auto it=ump.begin();it!=ump.end();it++) s.insert({it->second,it->first});
        for(auto it=s.begin();it!=s.end();++it) stk.push(it->second);
        while(k--){
            int top=stk.top();
            stk.pop();
            v.push_back(top);
        }
        return v;
    }
};