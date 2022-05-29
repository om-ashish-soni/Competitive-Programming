# problem link : https://www.codechef.com/START2B/problems/T20MCH
# solution : below code

r,o,c=map(int,input().split())
# print(36*(20-o),r-c)
if int(36*(20-o))>r-c:
    print("YES")
else:print("NO")
