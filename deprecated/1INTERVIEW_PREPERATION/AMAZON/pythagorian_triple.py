# problem link : https://practice.geeksforgeeks.org/problems/pythagorean-triplet3018/1/#
# solution : below code
#User function Template for python3
class Solution:

    def checkTriplet(self,arr, n):
        lst=list(set(arr))
        n=len(lst)
        memo={}
        for num in lst:
            memo[int(num*num)]=True
        for i in range(n):
            for j in range(i+1,n):
                sm=int(lst[i]*lst[i])+int(lst[j]*lst[j])
                if sm in memo: return True
        return False
        # code here

#{ 
#  Driver Code Starts
#Initial Template for Python 3



if __name__ == '__main__':
    tc = int(input())
    while tc > 0:
        n = int(input())
        arr = list(map(int, input().strip().split()))
        ob = Solution()
        ans = ob.checkTriplet(arr, n)
        if ans:
            print("Yes")
        else:
            print("No")
        tc -= 1

# } Driver Code Ends
