# problem link : https://leetcode.com/explore/interview/card/top-interview-questions-easy/97/dynamic-programming/576/
# solution : below code
import copy
class Solution:
    def rob(self, nums: List[int]) -> int:
        if len(nums)==1: return nums[0]
        if len(nums)==2: return max(nums)
        dp=copy.deepcopy(nums)
        dp[2]+=dp[0]
        n=len(nums)
        for index in range(3,n):
            dp[index]+=max(dp[index-2],dp[index-3])
        return max(dp)
