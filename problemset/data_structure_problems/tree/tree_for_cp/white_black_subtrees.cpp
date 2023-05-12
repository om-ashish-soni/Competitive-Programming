// problem link : https://codeforces.com/problemset/problem/1676/G
// solution : below code 

pii dfs(vvi & graph,vc & color,int start,int &ctr){
	pii pr={0,0};
	if(color[start]=='W') pr.first++;else pr.second++;
	FEACH(node,graph[start]){
		pii incom=dfs(graph,color,node,ctr);
		pr.first+=incom.first;
		pr.second+=incom.second;
	}
	// cout<<start<<" : "<<pr.first<<" vs "<<pr.second<<endl;
	if(pr.first == pr.second) ctr++;
	return pr;
}
void solve(int t){
	//shree ganeshay namah
	int n;
	read(n);
	vvi graph(n+1);
	vi par(n-1);
	readv(par);
	F(i,0,n-1){
		graph[par[i]].pb(i+2);
	}
	vc color(n+1);
	F(i,1,n+1){
		cin>>color[i];
	}
	int ctr=0;
	dfs(graph,color,1,ctr);
	cout<<ctr<<endl;
}
