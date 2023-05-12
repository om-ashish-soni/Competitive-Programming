// problem link : https://codeforces.com/problemset/problem/1607/D
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
    vi v(n);
    vc tp(n);
    readv(v);
    readv(tp);
    disjointSet *ds=new disjointSet(n+10);
    vb visited(n+1,false);
    vi red,blue;
    F(i,0,n){

        if(tp[i]=='B') blue.pb(v[i]);
        else red.pb(v[i]);
    }
    SORT(blue);
    SORT(red);
    FEACH(num,blue){
        int place=ds->findSet(1);
        if(place<=num){
            visited[place]=true;
            ds->prefered_union(place,place+1);
        }
    }
    FEACH(num,red){
        num=max(num,1LL);
        num=min(num,n+1);
        int place=ds->findSet(num);
        if(place<=n){
            visited[place]=true;
            ds->prefered_union(place,place+1);
        }
    }

    // F(i,1,n+1){
    //     cout<<visited[i]<<" ";
    // }
    // cout<<endl;
    F(i,1,n+1){

        if(visited[i]==false){
            YESNO1(false);
            delete ds;
            return;
        }
    }
    YESNO1(true);
    delete ds;
    return;
    // kick(t);
    
    // write your answer here
    
    //complete your answer here
    // println();
}   
    
