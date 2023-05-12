class LCABinaryLifting{
	public:
	int n;
	int timer=0;
	vector<vector<int>> graph;
	vector<int> tin,tout;
	vector<vector<int>> up;
	int height=0;
	int root=0;
	LCABinaryLifting(vector<vector<int>> & graph,int root){
		this->n=(int)(graph.size());
		this->timer=0;
		this->graph=graph;
		this->tin.resize(n+1);
		this->tout.resize(n+1);
		this->height=ceil(log2(n+1));
		this->root=root;
		this->up.assign(n+1,vector<int>(height+1));
		visit(root,root);
	}
	void visit(int u,int parent){
		timer++;
		tin[u]=timer;
		up[u][0]=parent;
		for(int i=1;i<=height;i++){
			up[u][i]=up[up[u][i-1]][i-1];
		}
		for(auto node:graph[u]){
			if(node != parent){
				visit(node,u);
			}
		}
		tout[u]=timer;
	}
	inline bool isAnsestor(int u,int v){
		return (tin[u]<=tin[v] && tout[u]>=tout[v]);
	}
	int getLCA(int u,int v){
		if(isAnsestor(u,v)) return u;
		if(isAnsestor(v,u)) return v;
		for(int i=height;i>=0;i--){
			if(false==isAnsestor(up[u][i],v)){
				u=up[u][i];
			}
		}
		return up[u][0];
	}
	// user manual 
	static void how_to_use(){
		int n,m;
		cin>>n>>m;
		int root;
		cin>>root;
		vector<vector<int>> graph(n+1);
		for(int i=0;i<m;i++){
			int u,v;
			cin>>u>>v;
			graph[u].push_back(v);
			graph[v].push_back(u);
		}
		LCABinaryLifting *lbt=new LCABinaryLifting(graph,root);

		int q;
		cin>>q;
		for(int i=0;i<q;i++){
			int u,v;
			cin>>u>>v;
			int anc=lbt->getLCA(u,v);
			cout<<"u: "<<u<<" ,v: "<<v<<" ,anc = "<<anc<<endl;
		}
		delete lbt;
	}
};
