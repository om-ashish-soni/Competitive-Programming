def segBuild(lst,seg,leftIndex,rightIndex,index=0):
    if leftIndex==rightIndex:
        seg[index]=lst[leftIndex];return
    midIndex=int((leftIndex+rightIndex)/2)
    segBuild(lst,seg,leftIndex,midIndex,int(2*index+1))
    segBuild(lst,seg,midIndex+1,rightIndex,int(2*index+2))
    seg[index]=seg[int(2*index+1)]+seg[int(2*index+2)]
    
def segSum(seg,leftIndex,rightIndex,segLeft,segRight,index=0):
    if segLeft>rightIndex or segRight<leftIndex: return 0
    if segLeft>=leftIndex and segRight<=rightIndex:return seg[index]
    segMid=int((segLeft+segRight)/2)
    return segSum(seg,leftIndex,rightIndex,segLeft,segMid,2*index+1) + segSum(seg,leftIndex,rightIndex,segMid+1,segRight,2*index+2)

def segUpdate(seg,segLeft,segRight,pos,diff,index=0):
    if segLeft>pos or segRight<pos : return
    seg[index]+=diff
    if segLeft != segRight:
        segMid=int((segLeft+segRight)/2)
        segUpdate(seg,segLeft,segMid,pos,diff,2*index+1)
        segUpdate(seg,segMid+1,segRight,pos,diff,2*index+2)

# lst=[1,2,3,4]
# seg=[0 for _ in range(int(2*len(lst)))]
# segBuild(lst,seg,0,len(lst)-1)
# print(seg)
# print("sum from 2 to 4 : ",segSum(seg,1,3,0,len(lst)-1))
# segUpdate(seg,0,len(lst)-1,3,1)
# print("sum from 3 to 4 : ",segSum(seg,2,3,0,len(lst)-1))
    
    
