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

pref=[5]
for _ in range(9):
    pref.append(int(pref[-1]+5))
for _ in range(1,10):
    pref[_]+=pref[_-1]
for _ in range(1):
# for _ in range(int(input())):
    n,k=map(int,input().split())
    k=240-k;solved=0;l=0;r=9
    while l<r:
        mid=int((l+r)/2)
        if pref[mid]<=k: l=mid+1;solved=mid+1
        else : r=mid
    print(min(solved,n))
