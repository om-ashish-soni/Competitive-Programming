# problem link : https://www.codechef.com/START2B/problems/COLGLF5
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
    lst=[]
    lst.append([0,1])
    n,m=map(int,input().split())
    a=list(map(int,input().split()))
    b=list(map(int,input().split()))
    for num in a:
        lst.append([num,1])
    for num in b:
        lst.append([num,2])
    lst.sort()
    switched=0
    for i in range(1,len(lst)):
        if(lst[i][1] != lst[i-1][1]): 
            switched+=1
    print(switched)
    
    
