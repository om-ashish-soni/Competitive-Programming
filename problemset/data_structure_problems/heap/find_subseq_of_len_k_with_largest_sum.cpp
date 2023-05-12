// problem link : https://leetcode.com/problems/find-subsequence-of-length-k-with-the-largest-sum/description/
// solution : below code

class Solution {
public:
    vector<int> maxSubsequence(vector<int>& nums, int k) {
        priority_queue<pair<int,int>> pq;
        int index=-1;
        for(auto num:nums){
            index++;
            pq.push({-num,index});
            if(pq.size()>k){
                pq.pop();
            }
        }
        vector<pair<int,int>> v;
        while(pq.size()>0){
            pair<int,int> top=pq.top();
            pq.pop();
            v.push_back({top.second,-top.first});
        }
        sort(v.begin(),v.end());
        vector<int> seq;
        for(int i=0;i<k;i++){
            seq.push_back(v[i].second);
        }
        return seq;
    }
};