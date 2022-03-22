import sys,io,os,copy,heapq,bisect
from math import log2,ceil,gcd,floor
from sys import stdin,stdout
sys.setrecursionlimit(10**9)
isIo=True
# isIo=False

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
catalan=[0,1]
def findCatalan(n):
    if len(catalan)>n:return catalan[n]
    elif(len(catalan)<n): findCatalan(n-1)
    catalan.append(0)
    for num in range(1,n):
        catalan[n]+=catalan[num]*catalan[n-num]
findCatalan(25)
# for _ in range(1):
for _ in range(int(input())):
    n=int(input())
    print(findCatalan(n+1))
