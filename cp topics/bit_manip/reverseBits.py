# problem link : https://leetcode.com/explore/interview/card/top-interview-questions-easy/99/others/648/
# solution : below code
class Solution:
    def reverseBits(self, n: int) -> int:
        mask=[];bit=0
        while bit<32:
            mask.append(n%2)
            n>>=1
            bit+=1
        mask=mask[::-1]
        rev=0;mul=1
        for digit in mask:
            rev+=int(mul*digit)
            mul<<=1
        return rev
