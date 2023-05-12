# problem link : https://www.codechef.com/START2B/problems/CLASSES
# solution : below code

from sys import stdin,stdout
from math import log2,ceil,floor
import heapq
input=stdin.readline
def printend(*argv):
    output=""
    for arg in argv: output+=str(arg)+" "
    stdout.write(output)
def print(*argv):
    output=""
    for arg in argv: output+=str(arg)+" "
    stdout.write(output+"\n")
# for _ in range(1):
for _ in range(int(input())):
    n,m,s,k=map(int,input().split())
    inf=1e12+10
    graph=[[] for _ in range(n+1)]
    dist=[inf for _ in range(n+1)]
    pq=[[0,0]]
    dist[0]=0
    for _ in range(m):
        u,v=map(int,input().split())
        graph[u].append(v)
        graph[v].append(u)
    
    while(pq):
        d_v,v=heapq.heappop(pq)
        if d_v != dist[v] : continue
        # print("popped",v,d_v,len(pq))
        for node in graph[v]:
            if dist[node]>1+d_v:
                dist[node]=1+d_v
                # print("pushed",node,dist[node])
                heapq.heappush(pq,[dist[node],node])
    ump=[0 for _ in range(n+1)]
    lst=list(map(int,input().split()))
    for num in lst:ump[num]+=1
    pqd=[]
    for i in range(1,n+1):
        pqd.append([dist[i],i])
    heapq.heapify(pqd)
    
    tour=0
    # print(dist)
    while pqd:
        d_v,v=heapq.heappop(pqd)
        rem=min(ump[v],k)
        k-=rem
        tour+=int(d_v*2*rem)
    print(tour)
    
    
    
    
