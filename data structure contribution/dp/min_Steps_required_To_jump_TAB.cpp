class Solution {
public:
    int jump(vector<int>& nums) {
        vector<int> v(nums.size(),INT_MAX);
        v[0]=0;
        for(int i=0;i<nums.size();i++){
            for(int j=1;j<=nums[i];j++){
                if(i+j < nums.size()) v[i+j]=min(v[i+j],v[i]+1);
                else break;
            }
        }
        return v[nums.size()-1];
    }
};