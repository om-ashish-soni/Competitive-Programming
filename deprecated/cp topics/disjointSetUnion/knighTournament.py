# Problem link : https://codeforces.com/contest/356/problem/A
# Solution : below code
import sys,io,os,copy,heapq
from math import log2,ceil,gcd,floor
from sys import stdin,stdout
sys.setrecursionlimit(10**9)
# isIo=True
isIo=False

if isIo:
    stdin = open('input.txt', 'r')
    stdout = open('output.txt', 'w')
input=stdin.readline
def printend(*argv):
    output=""
    for arg in argv: output+=str(arg)+" "
    stdout.write(output)
def print(*argv):
    output=""
    for arg in argv: output+=str(arg)+" "
    stdout.write(output+"\n")

def findSet(ump,u):
    r=u
    while(ump[r]>=0):
        # print("in findset ",r)
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
def preferedUnion(ump,u,v):
    u=findSet(ump,u)
    v=findSet(ump,v)
    if(u==v): return False
    totalChilds=ump[u]+ump[v]
    ump[v]=u
    ump[u]=totalChilds
    return True
for _ in range(1):
# for _ in range(int(input())):
    # print("Hello")
    n,q=map(int,input().split())
    ump=[-1 for _ in range(n+2)]
    lost=[0 for _ in range(n+2)]
    for _ in range(q):
        l,r,winner=map(int,input().split())
        
        while(l<winner):
            # print(_,l,'L')
            l=findSet(ump,l)
            if l<winner : lost[l]=winner;preferedUnion(ump,winner,l)
            l=l+1
        right=winner+1
        while(right<=r):
            # print(_,r,"R")
            right=findSet(ump,right)
            if right<r+1 : lost[right]=winner;preferedUnion(ump,r+1,right)
            right=right+1
        # print("l : ",lost)
        # print("u : ",ump)
    for index in range(1,n+1):printend(lost[index])
    print()
