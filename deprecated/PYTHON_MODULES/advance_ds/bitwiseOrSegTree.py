def segBuild(seg,n):
    domain=n;start=domain-1
    while domain>0:
        for index in range(start,start+domain):
            seg[index]=(seg[int(2*index) + 1] | seg[int(2*index) + 2])
        domain=domain//2;start=domain-1
def segUpdate(seg,pos,val):
    domain=int(2**ceil(log2(pos)));pos-=1
    mypos=pos+ len(seg)//2
    seg[mypos]=val
    print(mypos)
    while mypos>0:
        mypos=mypos//2
        print(mypos)
        seg[mypos]=(seg[int(2*mypos) + 1] | seg[int(2*mypos) + 2])
