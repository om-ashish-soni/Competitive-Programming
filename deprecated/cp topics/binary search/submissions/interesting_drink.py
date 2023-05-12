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


for _ in range(1):
# for _ in range(int(input())):
    n=int(input())
    lst=sorted(list(map(int,input().split())))
    # print(lst)
    q=int(input())
    for _ in range(q):
        num=int(input())
        print(bisect.bisect(lst,num))
