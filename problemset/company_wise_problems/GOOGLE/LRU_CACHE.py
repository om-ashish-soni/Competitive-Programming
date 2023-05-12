# problem link : https://leetcode.com/problems/lru-cache/
# solution : below code

import heapq
class LRUCache:
    
    def __init__(self, capacity: int):
        self.memo={}
        self.accessTimer={}
        self.pq=[]
        self.capacity=capacity
        self.tm=0
        pass

    def get(self, key: int) -> int:
        self.tm+=1
        if key in self.memo:
            self.accessTimer[key]=self.tm
            heapq.heappush(self.pq,[self.tm,key])
            return self.memo[key]
        return -1
    def put(self, key: int, value: int) -> None:
        self.tm+=1
        self.memo[key]=value
        self.accessTimer[key]=self.tm
        while len(self.memo)>self.capacity:
            accesstm,oldkey=heapq.heappop(self.pq)
            if accesstm == self.accessTimer[oldkey] and ( oldkey in self.memo) : self.memo.pop(oldkey)
        heapq.heappush(self.pq,[self.tm,key])


# Your LRUCache object will be instantiated and called as such:
# obj = LRUCache(capacity)
# param_1 = obj.get(key)
# obj.put(key,value)
