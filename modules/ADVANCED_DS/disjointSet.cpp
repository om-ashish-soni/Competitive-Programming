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
        int r=u;
        while(ump[r]!=-1){
            r=ump[r];
        }
        while(u!=r){
            int par=ump[u];
            ump[u]=r;
            u=par;
        }
        return r;
    }
    void setUnion(int u,int v){
        int uroot=findSet(u);
        int vroot=findSet(v);
        if(uroot == vroot) return ;
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
        return;
    }
    void print(){
        for(auto &pr:ump){
            cout<<"{"<<pr.first<<"<="<<pr.second<<"}"<<endl;
        }
    }
};
int main() {
	// your code goes here
	vector<int> arr;
	arr.push_back(1);
	arr.push_back(2);
	arr.push_back(3);
	arr.push_back(4);
	disjointSet ds=*new disjointSet(arr);
	
	ds.print();
	return 0;
}
