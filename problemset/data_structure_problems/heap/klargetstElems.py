# problem link : https://practice.geeksforgeeks.org/problems/k-largest-elements4206/1/#
# company tags : amazon
#User function Template for python3
import heapq
class Solution:

    def kLargest(self,arr, n, k):
        pq=[]
        for i in range(k):
            pq.append(arr[i])
        heapq.heapify(pq)
        for i in range(k,n):
            heapq.heappush(pq,arr[i])
            heapq.heappop(pq)
        pq.sort()
        pq=pq[::-1]
       # print(pq)
        return pq
        # code here

#{ 
#  Driver Code Starts
#Initial Template for Python 3


if __name__ == '__main__':
    tc = int(input())
    while tc > 0:
        n, k = list(map(int, input().strip().split()))
        arr = list(map(int, input().strip().split()))
        ob = Solution()
        ans = ob.kLargest(arr, n, k)
        for x in ans:
            print(x, end=" ")
        print()
        tc -= 1

# } Driver Code Ends
