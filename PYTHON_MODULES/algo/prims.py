def prims(mst,graph,newsDist):
	n=len(graph)
	inf = int(1e24)
	isTake=[False for _ in range(n)]
	dist=[inf for _ in range(n)]
	par=[-1 for _ in range(n)]
	dist[0]=0
	pq=[]
	heapq.heapify(pq)
	heapq.heappush(pq,[0,0])
	sm=0
	while pq:
		topPair=heapq.heappop(pq)
		v=topPair[1]
		d_v=topPair[0]
		if isTake[v]: continue
		if d_v != dist[v] : continue
		if par[v] != -1:
			# print(par[v],v)
			sm+=dist[v]
			mst[par[v]].append([v,dist[v]])
			mst[v].append([par[v],dist[v]])
			# print(v,par[v],dist[v])
		isTake[v]=True
		for node,w in graph[v]:
			# print(v,node,w)
			if isTake[node] == False and dist[node]>w:
				par[node]=v
				dist[node]=w
				heapq.heappush(pq,[dist[node],node])
	# print("wgt : ",sm)
	dijkstra(mst,newsDist)
