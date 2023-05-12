# problem link : https://leetcode.com/explore/interview/card/top-interview-questions-easy/127/strings/887/
# solution : below code
class Solution:
    def longestCommonPrefix(self, strs: List[str]) -> str:
        lst=[]
        index=0
        while True:
            polute=False
            if(index>100): break
            print(index,lst)
            ch=""
            for s in strs:
                if len(s)<=index: 
                    if ch != "":lst.pop()
                    polute=True
                    break
                if ch=="":ch=s[index];lst.append(s[index])
                else:
                    if ch!=s[index]:lst.pop();polute=True;break
            index+=1 
            if polute: break
        return ''.join(lst)
            
