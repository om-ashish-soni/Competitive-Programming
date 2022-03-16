# problem link : https://codeforces.com/problemset/problem/431/C
# solution : below code

import sys,io,os,copy,heapq,bisect
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
    n,k,d=map(int,input().split())
    dp=[[1,0] for _ in range(n+1)]
    for _ in range(d,min(n+1,k+1)):
        dp[_][1]=1;dp[_][0]=0
    for _ in range(k+1,n+1):
        dp[_][0]=0
    mod=int(1e9 + 7)
    # for row in dp:print(row)
    for num in range(1,n+1):
        for offset in range(1,k+1):
            # print(num,offset)
            nxt=num+offset
            if nxt>n: break
            dp[nxt][1]+=dp[num][1]
            if offset>=d : 
                dp[nxt][1]+=dp[num][0]
                # if num<d and offset>=d : dp[nxt][1]+=1
            else: dp[nxt][0]+=dp[num][0]
            # print("dp[",nxt,"]",dp[nxt])
    print(dp[n][1]%mod)
# for _ in range(1):
# for _ in range(int(input())):
    # pass
