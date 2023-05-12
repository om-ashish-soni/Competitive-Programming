import sys
import copy
import math
import heapq
import threading
isIo=False
threading.stack_size(67108864)
sys.setrecursionlimit(10**6)
if(isIo):
	sys.stdin = open('input.txt', 'r')
	sys.stdout = open('output.txt', 'w')
isTakeTestCase=True
def scanIntList():
	return map(int,input().split())
def printList(lst):
	for elem in lst:
		print(elem,end=" ")
	print()

def findSet(ump,u):
	r=u
	while(ump[r]>=0):
		r=ump[r]
	while(u != r):
		par=ump[u]
		ump[u]=r
		u=par
	return r
def setUnion(ump,u,v):
	u=findSet(ump,u)
	v=findSet(ump,v)
	if(u==v): return False
	totalChilds=ump[u]+ump[v]
	if(ump[u]<=ump[v]):
		ump[v]=u
		ump[u]=totalChilds
	else :
		ump[u]=v
		ump[v]=totalChilds
	return True

def dijkstra(graph):
	inf = int(1e16)
	pq=[[0,0]]
	heapq.heapify(pq)
	n=len(graph)
	dist=[0]+[inf for _ in range(n-1)]
	par=[-1 for _ in range(n)]
	dijkstraCost=0
	while pq:
		d_v,v=heapq.heappop(pq)
		if d_v != dist[v] : continue
		if par[v] != -1: dijkstraCost+=dist[v]-dist[par[v]]
		for edge in graph[v]:
			node,w=edge
			if dist[node]>w+d_v:
				par[node]=v
				dist[node]=w+d_v
				heapq.heappush(pq,[dist[node],node])
			elif dist[node]==w+d_v and dist[node]-dist[par[node]]>w: par[node]=v
	if inf in dist: dijkstraCost=-1
	return dijkstraCost
def prims(graph):
	primsCost=0
	n=len(graph)
	inf = int(1e24)
	isTake=[False for _ in range(n)]
	dist=[inf for _ in range(n)]
	par=[-1 for _ in range(n)]
	dist[0]=0
	pq=[]
	heapq.heapify(pq)
	heapq.heappush(pq,[0,0])
	sm=0
	while pq:
		topPair=heapq.heappop(pq)
		v=topPair[1]
		d_v=topPair[0]
		if isTake[v]: continue
		if d_v != dist[v] : continue
		if par[v] != -1:
			primsCost+=dist[v]
		isTake[v]=True
		for node,w in graph[v]:
			if isTake[node] == False and dist[node]>w:
				par[node]=v
				dist[node]=w
				heapq.heappush(pq,[dist[node],node])
	return primsCost

def kruskal(n,edges,weights):
	mstCost=0
	weights.sort()
	ump=[-1 for _ in range(n)]
	for w,index in weights:
		u,v=edges[index]
		if setUnion(ump,u,v):
			mstCost+=w;
	return mstCost
def solve():
	n,m=scanIntList()
	inf = int(1e16)
	graph=[[] for _ in range(n)]
	edges=[]
	weights=[]
	for _ in range(m):
		u,v,w=scanIntList()
		edges.append([u,v])
		weights.append([w,_])
		graph[u].append([v,w])
		graph[v].append([u,w])
	primsCost=prims(graph)
	dijkstraCost=dijkstra(graph)
	if  dijkstraCost==-1: print("NO")
	elif  dijkstraCost==primsCost: print("YES")
	else : print("NO")
def driver():
	testCases=1
	if( isTakeTestCase ) :
		testCases=int(input())
	for i in range(testCases):
		solve()

driver()
