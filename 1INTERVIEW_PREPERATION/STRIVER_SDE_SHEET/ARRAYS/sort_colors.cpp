// problem link : https://leetcode.com/problems/sort-colors/
// solution : below code

class Solution {
public:
    void sortColors(vector<int>& nums) {
        
        int n=nums.size();
        int two=n,zero=-1;
        
        for(int i=0;i<two;i++){
            
            if(nums[i]==0){
                zero++;
                swap(nums[zero],nums[i]);
                if(zero != i) i--;
            }else if(nums[i]==2){
                two--;
                swap(nums[two],nums[i]);
                if(two != i) i--;
            }
        }
    }
};
