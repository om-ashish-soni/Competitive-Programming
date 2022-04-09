# problem link : https://leetcode.com/explore/interview/card/top-interview-questions-easy/99/others/565/
# solution : below code
class Solution:
    def hammingWeight(self, n: int) -> int:
        bit=0;ctr=0
        while bit<32:
            ctr+=(n%2)
            n>>=1
            bit+=1
        return ctr
