#include<bits/stdc++.h>
#define int long long 
#define endl "\n"
using namespace std;
const int mod1 = (1e9+7);
void print(bool b){
	cout<<((b)?("YES"):("NO"))<<endl;
}
int stringToInt(const string &s){
	stringstream om(s);
	int num=-1;
	om>>num;
	return num;
}

class Graph{
	public : 
	vector<vector<int>> graph;
	vector<vector<int>> solutionVectors;
	vector<int> colorOf;

	int n;
	int no_of_colors=0;
	Graph(int n){
		graph.resize(n+1);
		colorOf.assign(n+1,0);
		this->n=n;
	}
	void set_no_of_colors(int m){
		this->no_of_colors=m;
	}
	void addEdge(int u,int v){
		graph[u].push_back(v);
	}
	void printGraph(){
		for(int i=1;i<=n;i++){
			cout<<i<<" : ";
			for(auto neb:graph[i]){
				cout<<neb<<" ";
			}cout<<endl;
		}
	}
	void mcolor(int start){
		if(start>n){
			solutionVectors.push_back(colorOf);
			return;
		}
		vector<bool> isValidColor(no_of_colors+1,true);
		for(auto node:graph[start]){
			isValidColor[colorOf[node]]=false;
		}
		for(int i=1;i<=no_of_colors;i++){
			if(isValidColor[i]){
				colorOf[start]=i;
				this->mcolor(start+1);
			}
		}
		colorOf[start]=0;
		return;
	}
	void printSolutionVectors(){
		for(auto & row:solutionVectors){
			for(auto node:row){
				cout<<node<<" ";
			}
			cout<<endl;
		}
	}
	void hamiltonUtil(int root,int start,int par,vector<int>& recStack,vector<int>& callStack,int level=0){
		// cout<<start<<" "<<level<<endl;
		if(level==n && start==root){
			callStack.push_back(root);
			this->solutionVectors.push_back(callStack);
			callStack.pop_back();
			return;
		}
		if(recStack[start]) return;
		
		recStack[start]=true;
		callStack.push_back(start);
		for(auto node:graph[start]){
			if(node != par) hamiltonUtil(root,node,start,recStack,callStack,level+1);
		}
		callStack.pop_back();
		recStack[start]=false;
		return;
	}
	void hamilton(int root){
		vector<int> recStack(n,false);
		vector<int> callStack;
		this->hamiltonUtil(root,root,-1,recStack,callStack);
	}
};

void solve(){
	int n,edges;
	cin>>n>>edges;
	Graph g=*new Graph(n);
	for(int i=0;i<edges;i++){
		int u,v;
		cin>>u>>v;
		g.addEdge(u,v);
		g.addEdge(v,u);
	}
	cout<<"graph : "<<endl;
	g.printGraph();
	g.hamilton(0);
	cout<<"solution : "<<endl;
	g.printSolutionVectors();
}
signed main(){

	ios_base::sync_with_stdio(false);
    cin.tie(NULL);
#ifndef ONLINE_JUDGE 
    freopen("input.txt", "r", stdin);
    freopen("error.txt", "w", stderr);
    freopen("output.txt", "w", stdout);
#endif
	int t=1;
	// cin>>t;
	while(t--){
		solve();
	}
	cerr<<"time taken : "<<(float)clock()/CLOCKS_PER_SEC<<" secs"<<endl;
}
