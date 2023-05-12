# problem link : https://www.codechef.com/START34A/problems/BSXOR
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
    n,k=map(int,input().split())
    s=input()
    s=list(s[0:n])
    ones=s.count('1')
    if ones%2 == 1:
        if k%2==0:
            print("NO")
        elif ones>=k: 
            print("YES")
        else:
            print("NO")
    else:
        comps=0
        xorr=False
        for num in s:
            if num=='0':
                if xorr==False:comps+=1
            else:
                if xorr:
                    comps+=1
                    xorr=False
                else : 
                    xorr=True
        
        if comps>=k:print("YES")
        elif ones>=k and k%2==0:print("YES")
        else:print("NO")
    
    
    
