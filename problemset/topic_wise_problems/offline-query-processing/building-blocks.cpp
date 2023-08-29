// problem link : https://www.codingninjas.com/studio/contests/monthly-contest-17/9286791/problems/25287
// solution : below code

class disjointSet {
    vector<int> ump;
public:
    vector<int>& getUmp() {
        return ump;
    }
    disjointSet(int n) {
        ump.assign(n + 1, -1);
    }
    int findSet(int u) {
        // cout<<"in findSet "<<u<<endl;
        int r = u;
        while (ump[r] >= 0) {
            r = ump[r];
        }
        while (u != r) {
            int par = ump[u];
            ump[u] = r;
            u = par;
        }
        return r;
    }
    bool setUnion(int u, int v) {
        // cout<<"in setUnion "<<u<<" "<<v<<endl;
        int uroot = findSet(u);
        int vroot = findSet(v);
        // cout<<"root : "<<uroot<<" "<<vroot<<endl;
        if (uroot == vroot) return false;
        int uchild = ump[uroot];
        int vchild = ump[vroot];
        int totalChild = uchild + vchild;

        if (uchild > vchild) {
            ump[uroot] = vroot;
            ump[vroot] = totalChild;
        } else {
            ump[vroot] = uroot;
            ump[uroot] = totalChild;
        }
        return true;
    }
    bool prefered_union(int u, int v) {
        int uroot = findSet(u);
        int vroot = findSet(v);
        if (uroot == vroot) return false;
        int uchild = ump[uroot];
        int vchild = ump[vroot];
        int totalChild = uchild + vchild;
        ump[uroot] = vroot;
        ump[vroot] = totalChild;
        return true;
    }
    bool checkOdd(int l, int r) {
        for (int i = l; i <= r; i++) {
            // cout<<ump[i]<<" ";
            if (ump[i] < 0) {
                if (abs(ump[i]) % 2) return false;
            }
        }
        // cout<<endl;
        return true;
    }

    int getChilds(int u) {
        int root = findSet(u);
        return abs(ump[root]);
    }
};



vector<int> buildingBlocks(int n, int m, vector<vector<int>> &links, vector<int> &a, int k, vector<int> &d) {
    disjointSet *ds=new disjointSet(n+10);
    vector<bool> active(n,true);
    for(auto node:d){
        active[node]=false;
    }
    vector<int> score(n,0);
    
    priority_queue<pair<int,int>> pq;
    
    for(int i=0;i<n;i++){
        score[i]=a[i];
    }

    vector<vector<int>> graph(n);
    for(auto & link:links){
        int u,v;
        u=link[0];
        v=link[1];
        graph[u].push_back(v);
        graph[v].push_back(u);
    }
    for(int i=0;i<n;i++){
        if(!active[i]) continue;
        int u=i;
        pq.push({a[i],i});
        for(auto v:graph[u]){
            if(!active[v]) continue;
            int u_root=ds->findSet(u);
            int v_root=ds->findSet(v);
            
            if(u_root != v_root){
                ds->setUnion(u_root,v_root);
                int root=ds->findSet(u);
                score[root]=score[u_root]^score[v_root];
                if(root != u_root) score[u_root]=-1;
                if(root != v_root) score[v_root]=-1;
                pq.push({score[root],root});
            }
        }
    }
    
    vector<int> ans(k,0);
    int index=k-1;
    for(int i=k-1;i>=0;i--){
        // for(int i=0;i<n;i++) cout<<score[i]<<" ";cout<<endl;
        int u=d[i];
        active[u]=true;
        // cout<<"Join : "<<u<<endl;
        pq.push({a[u],u});
        for(auto v:graph[u]){
            if(!active[v]) continue;

            int u_root=ds->findSet(u);
            int v_root=ds->findSet(v);
            
            if(u_root != v_root){
                ds->setUnion(u_root,v_root);
                int root=ds->findSet(u);
                score[root]=score[u_root]^score[v_root];
                if(root != u_root) score[u_root]=-1;
                if(root != v_root) score[v_root]=-1;
                pq.push({score[root],root});
            }
        }
        int mx=0;
        while(pq.size()>0){
            pair<int,int> top=pq.top();
            int score_v=top.first;
            int v=top.second;
            int v_root=ds->findSet(v);
            if(score_v == score[v] && v_root == v){
                mx=max(mx,score_v);
                break;    
            }
            pq.pop();
        }
        // cout<<mx<<endl;
        ans[index--]=mx;
    }
    
    return ans;
}
