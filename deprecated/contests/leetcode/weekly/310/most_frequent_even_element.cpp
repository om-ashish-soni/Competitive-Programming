// problem link : https://leetcode.com/contest/weekly-contest-310/problems/most-frequent-even-element/
// solution : below code

class Solution {
public:
    int mostFrequentEven(vector<int>& nums) {
        map<int,int> mp;
        for(auto num:nums){
            if(num%2==0) mp[num]++;
        }
        int mx=-1;
        int freq=0;
        for(auto &pr:mp){
            if(freq<pr.second){
                mx=pr.first;
                freq=pr.second;
            }
        }
        return mx;
    }
};
