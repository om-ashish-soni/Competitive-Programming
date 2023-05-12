# problem link : https://www.codechef.com/problems/QHOUSE
# solution : below code
area=0;a=0;b=0;c=0
# for square
a=0;l=0;r=1000
while l<=r:
    flag=True
    if l==r:flag=False
    mid=int((l+r)/2)
    print('?',mid,0)
    s=input()
    # s=s[0:len(s)-1]
    if s=="YES":
        l=mid+1;a=max(a,mid)
    else:r=mid
    if flag==False:break
a=int(a*2)
# print("a : ",a)

l=0;r=1000
while l<=r:
    flag=True
    if l==r:flag=False
    mid=int((l+r)/2)
    print('?',mid,a)
    s=input()
    # s=s[0:len(s)-1]
    if s=="YES":
        l=mid+1;b=max(b,mid)
    else:r=mid
    if flag==False:break
b=int(b*2)

# print("b : ",b)

l=a;r=1000
while l<=r:
    flag=True
    if l==r:flag=False
    mid=int((l+r)/2)
    print('?',0,mid)
    s=input()
    # s=s[0:len(s)-1]
    if s=="YES":
        l=mid+1;c=max(c,mid)
    else:r=mid
    if flag==False:break

c=c-a
# print("c : ",c)
area=int(a*a)+int(b*c/2)
print('!',area)
    
    
    
