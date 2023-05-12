# problem link : https://www.codechef.com/problems/SWAP10HG
# solution : below code
def reject():
    print("No")
for _ in range(int(input())):
    n=int(input());s=list(input());p=list(input())
    z1=s.count('0');z2=p.count('0')
    if z1 != z2 : reject();continue
    lag=0;rejected=False
    for i in range(n):
        if s[i] != p[i]:
            if s[i]=='0':
                if lag>0:lag-=1
                else:rejected=True;break
            else:
                if lag<0:rejected=True;break
                else:lag+=1
    if rejected==False and lag==0:print("Yes")
    else:print("No")
