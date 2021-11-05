class Solution {
public:
    void lengthOfLIS(vector<int>& nums,vector<int> &v,int i=0){
        if(i==nums.size()) return;
        lengthOfLIS(nums,v,i+1);
        int mx=0;
        for(int j=i+1;j<nums.size();j++){
            if(nums[i]<nums[j]){
                mx=max(mx,v[j]);
            }
        }
        v[i]=mx+1;
        return;
    }
    int lengthOfLIS(vector<int>& nums) {
        vector<int> numbers;
        numbers.push_back(INT_MIN);
        for(auto num:nums){
            numbers.push_back(num);
        }
        vector<int> v(nums.size()+1,0);
        v[0]=0;
        lengthOfLIS(numbers,v);
        // cout<<v[0]-1<<endl;
        return v[0]-1;
    }
};