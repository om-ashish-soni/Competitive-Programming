# problem link : https://www.codechef.com/START2B/problems/PGRID1
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
    n=int(input())
    lst=list(map(int,input().split()))
    lst=lst[::-1]
    coverup=0
    cost=0
    for num in lst:
        if coverup>0:coverup-=1
        if coverup<num:
            cost+=num-coverup
        coverup=num
    print(cost)
    
