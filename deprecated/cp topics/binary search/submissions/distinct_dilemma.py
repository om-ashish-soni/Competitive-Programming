# problem link : https://www.codechef.com/START33B/problems/DISTDILEM
# solution : below code
import bisect
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
bst=[1]
for i in range(2,100001):
    bst.append(i+bst[-1])
# for _ in range(1):
for _ in range(int(input())):
    n=int(input())
    lst=list(map(int,input().split()))
    sm=sum(lst)
    print(bisect.bisect(bst,sm))
    # print(bst[-1])
