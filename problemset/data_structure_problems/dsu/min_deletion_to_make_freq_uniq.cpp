// problem link : https://leetcode.com/problems/minimum-deletions-to-make-character-frequencies-unique/description
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

    int getChilds(int u){
        int root=findSet(u);
        return abs(ump[root]);
    }
};

class Solution {
public:
    int minDeletions(string s) {
        int n=s.size();
        disjointSet *ds=new disjointSet(n+1);
        int ctr=0;
        map<char,int> mp;
        for(auto c:s){
            mp[c]++;
        }
        vector<int> v;
        for(auto & pr:mp){
            v.push_back(pr.second);
        }
        sort(v.begin(),v.end());
        int sz=v.size();
        for(int i=0;i<sz;i++){
            int freq=v[i];
            // cout<<"freeq : "<<freq<<endl;
            int root=ds->findSet(freq);
            int delta=freq-root;
            ctr+=delta;
            if(root>0) ds->prefered_union(root,root-1);
        }
        delete ds;
        return ctr;
    }
};