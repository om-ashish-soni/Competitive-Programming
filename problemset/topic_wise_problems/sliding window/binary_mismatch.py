# problem link : https://www.codechef.com/START34A/problems/BINMIS
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
    s=input()
    s=list(s[0:n])
    if n%2==1:print("NO")
    else:
        l=0
        r=0
        ones=s.count('1')
        diff=ones-(n//2)
        curr=0
        for num in s:
            if num=='0':curr-=1
            else:curr+=1
            if curr==diff:break
            r+=1
        print("YES")
        print(l+1,r+1)
    
    
