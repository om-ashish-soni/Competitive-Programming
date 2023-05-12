#include<bits/stdc++.h>
using namespace std;
#define YESNO2(b) cout<<((b)?("Yes"):("No"))<<endl;
#define ll long long
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

    int getChilds(int u){
        int root=findSet(u);
        return abs(ump[root]);
    }
};

namespace Solution {
    ll limit=2e5+10;
    vector<ll> factors(limit,2);
    void init(){
        factors[1]=1;
        factors[0]=0;
        for(int i=2;i<limit;i++){
            for(int j=i+i;j<limit;j+=i){
                factors[j]++;
            }
        }
    }
    void solve(){
        init();
        int n;
        cin>>n;

        ll ctr=0;
        for(int i=1;i<n;i++){
            ll first=factors[i];
            ll second=factors[n-i];
            ctr+=first*second;
        }
        cout<<ctr<<endl;
        
    }
} // Solution
    
int main(){
    int t=1;
    // cin>>t;
    while(t--) Solution::solve();
    return 0;
}