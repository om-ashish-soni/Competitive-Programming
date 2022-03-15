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

def checkRadius(lst,diff,l):
    if lst[0]-diff>0 or lst[-1]+diff<l:return False
    for index in range(1,len(lst)):
        if lst[index-1]+diff <lst[index]-diff: return False
    return True
for _ in range(1):
# for _ in range(int(input())):
    n,l=map(int,input().split())
    lst=list(map(int,input().split()))
    lst.sort();diff=max(lst[0],l-lst[-1])
    for index in range(1,n):
        diff=max(diff,lst[index]-lst[index-1])
    left=0;right=diff
    while left<right:
        mid=(left+right)/2
        if checkRadius(lst,mid,l) : right=ceil(mid)-1;diff=mid
        else : left=ceil(mid)
    if left==right:
        if checkRadius(lst,left,l):diff=min(diff,left)
    print(diff)
