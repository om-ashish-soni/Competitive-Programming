// problem link : https://leetcode.com/problems/find-all-duplicates-in-an-array/description/
// solution : below code

class Solution {
public:
    vector<int> findDuplicates(vector<int>& nums) {
        int n=nums.size();
        vector<int> v(n+1,0);
        for(int i=0;i<=n;i++){
            v[i]=-2*(i+1);
        }
        for(auto num:nums){
            v[num-1]+=num;
        }
        int index=0;
        for(int i=0;i<n;i++){
            if(v[i]==0){
                v[index]=i+1;
                index++;
            }
        }
        while(v.size()>index){
            v.pop_back();
        }
        return v;
    }
};