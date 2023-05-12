import sys,io,os,copy,heapq,bisect
from collections import deque
from itertools import permutations
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


# for _ in range(1):
for _ in range(int(input())):
    n,k=map(int,input().split())
    l=0;r=int(1e18 + 1);ans=-1
    while l<r:
        mid=int((l+r)/2)
        nonDiv=int(mid-int(mid/n))
        diff=nonDiv-k
        # print(mid,nonDiv,diff)
        if diff>=0:
            mod=mid%n
            if mod==0 or diff>=mod:diff+=1
            if diff<n:
                ans=mid-diff;break
            else:
                r=mid

        else : l=mid+1
    print(ans)
