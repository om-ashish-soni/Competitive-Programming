# problem link : https://www.codechef.com/START33B/problems/BRKNLIFE
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
chars=['a','b','c','d','e']
memo={}
memo['a']=1
memo['b']=2
memo['c']=3
memo['d']=4
memo['e']=0
def next(c):
    return chars[memo[c]]
def reject():
    print(-1)
# for _ in range(1):
for _ in range(int(input())):
    n,m=map(int,input().split())
    s=input()
    s=list(s[0:n])
    a=input()
    a=list(a[0:m])
    ai=0
    for i in range(n):
        if s[i]==a[ai]:
            ai+=1
        if ai>=m: break
        if s[i]=='?':
            s[i]=next(a[ai])
        
    if ai>=m: reject();continue
    s=''.join(s)
    print(s)
    
    
