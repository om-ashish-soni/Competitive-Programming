// problem link : https://binarysearch.com/problems/Number-of-Islands
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
int convert(int a,int b,int m){
    return a*m+b;
}
int solve(vector<vector<int>>& matrix) {
    int n=matrix.size();
    int m=matrix.front().size();
    disjointSet *ds=new disjointSet(n*m+10);
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            if(matrix[i][j]==0) continue;
            if(i+1<n && matrix[i+1][j]==1){
                ds->setUnion(convert(i,j,m),convert(i+1,j,m));
            }
            if(j+1<m && matrix[i][j+1]==1){
                ds->setUnion(convert(i,j,m),convert(i,j+1,m));
            }
        }
    }
    int ctr=0;
    map<int,bool> mp;
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            if(matrix[i][j]==0) continue;
            int root=ds->findSet(convert(i,j,m));
            mp[root]=true;
        }
    }
    ctr=mp.size();
    delete ds;
    return ctr;
}
