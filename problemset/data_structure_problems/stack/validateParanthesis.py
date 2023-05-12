# problem link : https://leetcode.com/explore/interview/card/top-interview-questions-easy/99/others/721/
# solution : below code
class Solution:
    def isValid(self, s: str) -> bool:
        couple={}
        couple[')']='('
        couple[']']='['
        couple['}']='{'
        stk=[]
        for ch in s:
            if ch in couple:
                if len(stk)>0 and stk[-1]==couple[ch]:stk.pop()
                else: return False
            else:
                stk.append(ch)
        return len(stk)==0
