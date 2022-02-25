
def findSet(ump,u):
	r=u
	while(ump[r]>=0):
		r=ump[r]
	while(u != r):
		par=ump[u]
		ump[u]=r
		u=par
	return r

def setUnion(ump,u,v):
	u=findSet(ump,u)
	v=findSet(ump,v)
	if(u==v): return False
	totalChilds=ump[u]+ump[v]
	if(ump[u]<=ump[v]):
		ump[v]=u
		ump[u]=totalChilds
	else :
		ump[u]=v
		ump[v]=totalChilds
	return True

def kruskal(n,edges,weights):
	mstCost=0
	weights.sort()
	ump=[-1 for _ in range(n)]
	for w,index in weights:
		u,v=edges[index]
		if setUnion(ump,u,v):
			mstCost+=w;
	return mstCost
