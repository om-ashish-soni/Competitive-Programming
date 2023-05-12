import sys
import copy
import math
isIo=True

sys.setrecursionlimit(10**6)
if(isIo):
	sys.stdin = open('input.txt', 'r')
	sys.stdout = open('output.txt', 'w')
isTakeTestCase=False
def scanIntList():
	return map(int,input().split())
def printList(lst):
	for elem in lst:
		print(elem,end=" ")
	print()


def markDistance(tree,isSpecial,dist,parentOfSpec,root,par,distanceFromRoot):
	dist[root]=distanceFromRoot+1
	dep=int(1e10)
	depSpec=-1
	if(root in isSpecial) : 
		parentOfSpec[root]=root
		dep=0
		depSpec=root
	for node in tree[root]:
		if(par != node):
			specNode,tempDep=markDistance(tree,isSpecial,dist,parentOfSpec,node,root,distanceFromRoot+1)
			if(dep>tempDep):
				dep=tempDep
				depSpec=specNode
	# print(root,depSpec)
	parentOfSpec[root]=depSpec
	return parentOfSpec[root],dep+1
def dfs(tree,dist,parentOfSpec,objective,myspec,root,par,specAnc):
	# print(root,parentOfSpec[root])
	if parentOfSpec[root] != -1:
		objective[root]=dist[root]
		specAnc=root
		myspec[root]=parentOfSpec[root]
	else:
		objective[root]=2*dist[specAnc]-dist[root]
		myspec[root]=parentOfSpec[specAnc]
	for node in tree[root]:
		if(par != node):
			dfs(tree,dist,parentOfSpec,objective,myspec,node,root,specAnc)
def reject():
	print(-1)

def constructTree(tree,score,lst,root,par,level):
	level+=1
	pair=[0,0]
	if(level%2==0):pair[0]+=lst[root]
	else : pair[1]+=lst[root]
	for node in tree[root]:
		if node != par : 
			comingPair=constructTree(tree,score,lst,node,root,level)
			pair[0]+=comingPair[0]
			pair[1]+=comingPair[1]
	# print(root,pair)
	score[root]=pair
	return pair

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
def solve():
	n,q=scanIntList()
	ump=[0] + [-1 for i in range(1,n+1)]
	toBeRemoved=0
	for _ in range(q):
		u,v=scanIntList()
		if(setUnion(ump,u,v)==False): toBeRemoved+=1
	print(toBeRemoved)
def driver():
	testCases=1
	if( isTakeTestCase ) :
		testCases=int(input())
	for i in range(testCases):
		solve()

driver()
