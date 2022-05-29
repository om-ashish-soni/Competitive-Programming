# problem link : https://www.codechef.com/START2B/problems/NOBEL
# solution : below code

from sys import stdin,stdout
from math import log2,ceil,floor
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
    n,m=map(int,input().split())
    lst=list(map(int,input().split()))
    memo={}
    for num in lst:memo[num]=True
    sz=len(memo)
    if sz<m:print("Yes")
    else : print("No")
    
    
