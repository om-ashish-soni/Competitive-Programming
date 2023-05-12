// Problem link : https://leetcode.com/problems/maximum-subarray/submissions/
// Problme type : divide and conquer
// Solution approach : divide and conquer
class Solution {
public:
    int crossingSubArray(vector<int>&nums,int left,int mid,int right){
        int leftSum=INT_MIN,rightSum=INT_MIN,sum=0;
        for(int i=mid;i>=left;i--){
            sum+=nums[i];
            if(sum>leftSum){
                leftSum=sum;
            }
            
        }
        sum=0;
        for(int i=mid+1;i<=right;i++){
            sum+=nums[i];
            if(sum>rightSum){
                rightSum=sum;
            }
        }
        return leftSum+rightSum;
    }
    int partitionSubArray(vector<int>& nums,int left,int right){
        if(left>right) return INT_MIN;
        if(left==right) return nums[left];
        int mid=left+(right-left)/2;
        int lSum=partitionSubArray(nums,left,mid);
        int rSum=partitionSubArray(nums,mid+1,right);
        int cSum=crossingSubArray(nums,left,mid,right);
        return max(lSum,max(rSum,cSum));
    }
    int maxSubArray(vector<int>& nums) {
        return partitionSubArray(nums,0,nums.size()-1);
    }
};
