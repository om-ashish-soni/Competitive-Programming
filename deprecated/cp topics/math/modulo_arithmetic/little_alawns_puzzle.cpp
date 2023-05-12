// problem link : https://codeforces.com/problemset/problem/1534/C
// solution : below code

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

    
};

void solve(int t){
    //shree ganeshay namah  
    int n;
    read(n);
    vpii v(n);
    F(i,0,n) read(v[i].first);
    F(i,0,n) read(v[i].second);
    disjointSet *ds=new disjointSet(n+10);
    map<int,bool> mp;

    F(i,0,n){
        ds->setUnion(v[i].first,v[i].second);
    }

    F(i,1,n+1){
        int root=ds->findSet(i);
        mp[root]=true;
    }
    int sz=mp.size();

    int ctr=power(2LL,sz,MOD1);
    println(ctr);
    delete ds;
    // kick(t);
    
    // write your answer here
    
    //complete your answer here
    // println();
}   
