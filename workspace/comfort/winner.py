def solve():
    n=int(input())
    lst=list(map(int,input().split()))
    ctr=0
    n=len(lst)
    bit=0
    index=0
    while index<n:
        if(bit==0):
            ctr+=lst[index]
            if(index+1<n and lst[index+1]==0):
                index+=1
                pass
            index+=1
            pass
        else:
            if(index+1<n and lst[index+1]==1):
                index+=1
                pass
            pass
            index+=1
            pass
        bit^=1
        pass
    print(ctr)
    pass

def drive(take):
    t=1
    if(take): t=int(input())
    for _ in range(t):
        solve()    
        pass
    pass

drive(True)
