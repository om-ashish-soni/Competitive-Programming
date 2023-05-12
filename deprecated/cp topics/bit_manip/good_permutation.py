# problem link : https://www.codechef.com/START34A/problems/GDPERM
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
    if n%2==0:
        lst=[_+1 for _ in range(n)]
        for i in range(0,n,2):
            lst[i],lst[i+1]=lst[i+1],lst[i]
        for num in lst:printend(num)
        print()
    else:
        if n<5:print(-1)
        else:
            lst=[_+1 for _ in range(n-5)]
            for i in range(0,n-5,2):
                lst[i],lst[i+1]=lst[i+1],lst[i]
            diff=n-5
            dummy=[4,1,2,5,3]
            
            for num in lst:printend(num)
            for num in dummy:printend(num+diff)
            print()
    
    
