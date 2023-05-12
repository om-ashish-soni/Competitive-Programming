// problem link : https://codeforces.com/problemset/problem/1559/D1
// solution : below code

// disjointSet
class disjointSet{
    vector<int> ump;
    public:
    vector<int>& getUmp(){
    	return ump;
    }
    disjointSet(int n){
        ump.assign(n+1,-1);
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
        // cout<<"root : "<<uroot<<" "<<vroot<<endl;
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
    bool prefered_union(int u,int v){
    	int uroot=findSet(u);
    	int vroot=findSet(v);
    	if(uroot==vroot) return false;
    	int uchild=ump[uroot];
        int vchild=ump[vroot];
        int totalChild=uchild+vchild;
        ump[uroot]=vroot;
        ump[vroot]=totalChild;
        return true;
    }
    bool checkOdd(int l,int r){
    	for(int i=l;i<=r;i++){
    		// cout<<ump[i]<<" ";
    		if(ump[i]<0){
    			if(abs(ump[i])%2) return false;
    		}
    	}
    	// cout<<endl;
    	return true;
    }

    // void giveConnectedComps(vector<vector<int>>& comps){
    // 	for(auto &pr:ump){
    // 		if(pr.first==0) continue;
    // 		if(pr.second > 0){
    // 			comps[pr.second].push_back(pr.first);
    // 		}else{
    // 			comps[pr.first].push_back(pr.first);
    // 		}
    // 	}
    // 	return;
    // }
    // void print(){
    //     for(auto &pr:ump){
    //         cout<<"{"<<pr.first<<"<="<<pr.second<<"}"<<endl;
    //     }
    // }
};

void solve(int t){
	//shree ganeshay namah
	int n;
	read(n);
	int a,b;
	read(a,b);
	disjointSet *dsa,*dsb;
	dsa=new disjointSet(n+2);
	dsb=new disjointSet(n+2);
	F(i,0,a){
		int u,v;
		read(u,v);
		dsa->setUnion(u,v);
	}
	F(i,0,b){
		int u,v;
		read(u,v);
		dsb->setUnion(u,v);
	}
	
	vpii edges;
	F(i,1,n+1){
		F(j,1,n+1){
			if(dsa->findSet(i) != dsa->findSet(j) && dsb->findSet(i) != dsb->findSet(j)){
				edges.pb({i,j});
				dsa->setUnion(i,j);
				dsb->setUnion(i,j);
			}
		}
	}
	int sz=edges.size();
	println(sz);
	FEACH(pr,edges){
		println(pr.first,pr.second);
	}
	delete dsa;
	delete dsb;

	// print answers here

}
