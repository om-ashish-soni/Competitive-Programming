#include <bits/stdc++.h>
using namespace std;
class disjointSet{
    unordered_map<int,int> ump;
    public:
    disjointSet(){}
    disjointSet(vector<int>& arr){
        for(auto num:arr) ump[num]=-1;
    }
    int findSet(int u){
        // cout<<"in findSet "<<u<<endl;
        int r=u;
        while(ump[r]>=0){
            r=ump[r];
        }
        while(u!=r){
            int par=ump[u];
            ump[u]=r;
            u=par;
        }
        return r;
    }
    bool setUnion(int u,int v){
        // cout<<"in setUnion "<<u<<" "<<v<<endl;
        int uroot=findSet(u);
        int vroot=findSet(v);
        if(uroot == vroot) return false;
        int uchild=ump[uroot];
        int vchild=ump[vroot];
        int totalChild=uchild+vchild;
        
        if(uchild>vchild){
            ump[uroot]=vroot;
            ump[vroot]=totalChild;
        }else{
            ump[vroot]=uroot;
            ump[uroot]=totalChild;
        }
        return true;
    }
    void print(){
        for(auto &pr:ump){
            cout<<"{"<<pr.first<<"<="<<pr.second<<"}"<<endl;
        }
    }
};
static bool comp(pair<int,int>& a,pair<int,int>&  b){
    return a.first<b.second;
}
int main() {
	// your code goes here
	//initailization of graph
	int no_of_vertices=0;
	cin>>no_of_vertices;
	cout<<"No of Vertices : "<<no_of_vertices<<endl;
	
	vector<int> arr;
	for(int i=0;i<no_of_vertices;i++) arr.push_back(i+1);
	disjointSet ds=*new disjointSet(arr);
	
	
	// scanning edges
	int no_of_edges=0;
	cin>>no_of_edges;
	cout<<"No of Edges : "<<no_of_edges<<endl;
	int u[no_of_edges],v[no_of_edges];
	vector<pair<int,int>> w(no_of_edges);
	for(int i=0;i<no_of_edges;i++){
	    cin>>u[i]>>v[i];
	    int weight;
	    cin>>weight;
	    w[i]={weight,i};
	}
	// sorting edges with original indices
	sort(w.begin(),w.end(),comp);
	
	//preparing mst
	vector<pair<int,int>> mst;
	for(auto &pr:w){
	    int index=pr.second;
	    int firstVertex=u[index];
	    int secondVertex=v[index];
	    int weight=pr.first;
	    if(ds.setUnion(firstVertex,secondVertex)){
	        mst.push_back(pr);
	    }
	    
	}
	// printing mst and gathering total cost of mst
	int totalCost=0;
	for(auto &pr:mst){
	    int index=pr.second;
	    cout<<"{ "<<u[index]<<" <-> "<<v[index]<<" } : "<<pr.first<<endl;
	    totalCost+=pr.first;
	}
	cout<<"MST SIZE : "<<mst.size()<<endl;
	cout<<"TOTAL COST : "<<totalCost<<endl;
	
	// completed
	return 0;
}
