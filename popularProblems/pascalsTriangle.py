# problem link: https://leetcode.com/explore/interview/card/top-interview-questions-easy/99/others/601/
# solution : below code
class Solution:
    def generate(self, numRows: int) -> List[List[int]]:
        lst=[[1]];numRows-=1
        while numRows>0:
            prev=lst[-1]
            curr=[1]
            for index in range(1,len(prev)):
                curr.append(prev[index]+prev[index-1])
            curr.append(1)
            lst.append(curr)
            numRows-=1
        return lst
