# problem link : https://leetcode.com/explore/interview/card/top-interview-questions-easy/99/others/762/
# solution : below code
class Solution:
    def hammingDistance(self, x: int, y: int) -> int:
        bit=0;ctr=0
        while bit<32:
            if x%2 != y%2: ctr+=1
            x>>=1;y>>=1
            bit+=1
        return ctr
