# problem link : https://leetcode.com/explore/interview/card/top-interview-questions-easy/99/others/722/
# solution : below code
class Solution:
    def missingNumber(self, nums: List[int]) -> int:
        sm=sum(nums)
        n=len(nums)
        total=(n*(n+1))//2
        return total-sm
