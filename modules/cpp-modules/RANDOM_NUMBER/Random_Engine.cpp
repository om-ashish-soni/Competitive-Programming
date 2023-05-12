class RandomEngine{

    mt19937 mt;
public:
    RandomEngine(){
        mt19937 smt(time(nullptr));
        this->mt=smt;
    }
    RandomEngine(int seed){
        mt19937 smt(seed);
        this->mt=smt;   
    }
    int get(){
        return mt();
    }
    int get(int n){
        return get()%n;
    }
    int get(int l,int r){
        int window=r-l+1;
        return get(window)+l;
    }
    vector<int> get_random_vector(int n){
        vector<int> v(n);
        disjointSet *ds=new disjointSet(n+1);
        F(i,0,n){
            int rem=n-i;
            int index=get(rem);
            int root=ds->findSet(index);
            ds->prefered_union(root,root+1);
            v[i]=root;
        }
        // printv(v);
        delete ds;
        return v;
    }
    static void how_to_use(){
        RandomEngine *rng=new RandomEngine();
        cout<<rng->get()<<endl;
        cout<<rng->get(10)<<endl;
        cout<<rng->get(20,30)<<endl;
    }
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

        int getChilds(int u){
            int root=findSet(u);
            return abs(ump[root]);
        }
    };
};
