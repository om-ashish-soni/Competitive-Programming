# problem link : https://www.codechef.com/START2B/problems/SVRT
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
    mod=n%m
    if mod==0:mod=m
    print(ceil(n/m),mod)
    
    
