def dijkstra(graph):
	inf = int(1e16)
	pq=[]
	heapq.heapify(pq)
	heapq.heappush(pq,[0,0])
	n=len(graph)
	dist=[inf for _ in range(n)]
	par=[-1 for _ in range(n)]
	dist[0]=0
	dijkstraCost=0
	while pq:
		topPair=heapq.heappop(pq)
		v=topPair[1]
		d_v=topPair[0]
		if d_v != dist[v] : continue
		# print(par[v],v,dist[v]-dist[par[v]])
		if par[v] != -1:
			dijkstraCost+=dist[v]-dist[par[v]]
		for edge in graph[v]:
			node,w=edge
			if dist[node]>w+d_v:
				par[node]=v
				dist[node]=w+d_v
				heapq.heappush(pq,[dist[node],node])
			elif dist[node]==w+d_v:
				if dist[node]-dist[par[node]]>w:
					par[node]=v
	if inf in dist:
		dijkstraCost=-1
	# print("dijkstraCost : ",dijkstraCost)
	return dijkstraCost
