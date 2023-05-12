// problem link : https://binarysearch.com/problems/First-Missing-Positive
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
int solve(vector<int>& nums) {
    int n=nums.size();
    disjointSet *ds=new disjointSet(n+10);
    for(auto num:nums){
        if(num>0 && num<=n){
            ds->prefered_union(num,num+1);
        }
    }  
    int root=ds->findSet(1);
    return root;
}
