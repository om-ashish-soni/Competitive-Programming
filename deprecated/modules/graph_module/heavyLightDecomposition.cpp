class HLD{
    vector<int> parent,depth,heavy,head,pos;
    vector<vector<int>> graph;
    vector<int> vals;
    int n=0;
    int curr_pos=0;
    MaxLazySegmentTree *st=NULL;
public: 
    HLD(vector<vector<int>> & graph,vector<int>& vals){
        this->graph=graph;
        this->n=this->graph.size();
        this->vals=vals;
        init();
    }
    int dfsTrip(int start){
        int subtreeSize=1;
        int maxChildSubtreeSize=0;
        for(auto & node: graph[start]){
            if(parent[start] != node){
                parent[node]=start;
                depth[node]=depth[start]+1;
                int childSubtreeSize=dfsTrip(node);
                subtreeSize+=childSubtreeSize;
                if(childSubtreeSize>maxChildSubtreeSize){
                    maxChildSubtreeSize=childSubtreeSize;
                    heavy[start]=node;
                }
            }
        }
        return subtreeSize;
    }
    void decompose(int start,int leader){
        head[start]=leader;
        pos[start]=curr_pos++;
        if(heavy[start]!=-1){
            decompose(heavy[start],leader);
        }
        for(auto & node:graph[start]){
            if(parent[start] != node && heavy[start] != node){
                decompose(node,node);
            }
        }
    }
    void init(){
        this->parent.assign(n,-1);
        this->depth.assign(n,0);
        this->heavy.assign(n,-1);
        this->head.assign(n,-1);
        this->pos.assign(n,0);
        this->curr_pos=0;
        dfsTrip(0);
        decompose(0,0);
        initializeSegmentTree();
    }
    int query(int a,int b){
        // cout<<"a : "<<a<<" , b : "<<b<<endl;
        int res=0;
        for(;head[a] != head[b];b=parent[head[b]]){
            // cout<<"in for loop : "<<" a : "<<a<<" , b : "<<b<<endl;

            if(depth[head[a]]>depth[head[b]]){
                swap(a,b);
            }
            // cout<<"getting query from : "<<head[b]<<" , "<<b<<endl;

            int currHeavyPathRes=st->getMax(pos[head[b]],pos[b]);
            // cout<<"pos from : "<<pos[head[b]]<<" , "<<pos[b]<<" with val : "<<currHeavyPathRes<<endl;
            res=max(res,currHeavyPathRes);
        }
        // cout<<"out for loop : "<<" a : "<<a<<" , b : "<<b<<endl;
        if(depth[a]>depth[b]){
            swap(a,b);
        }
        int lastHeavyPathRes=st->getMax(pos[a],pos[b]);
        res=max(res,lastHeavyPathRes);
        // cout<<"query : "<<a<<" , "<<b<<" : "<<res<<endl;
        // cout<<"pos : "<<pos[a]<<" , "<<pos[b]<<endl;
        return res;
    }
    void initializeSegmentTree(){
        this->st=new MaxLazySegmentTree(n);
        for(int i=0;i<n;i++){
            this->st->updateRange(pos[i],pos[i],vals[i]);
        }
    }
    void print(){
        printv(head);
        printv(parent);
        printv(heavy);
        printv(depth);
        printv(vals);
        // for(int i=0;i<n;i++){
        //     cout<<"i : "<<i<<" , pos[i] : "<<pos[i]<<" , vals[i] : "<<st->getMax(i,i)<<endl;
        // }
    }
    static void how_to_use(){
        int n;
        cin>>n;
        int m;
        cin>>m;
        vector<vector<int>> graph(n);
        for(int i=0;i<m;i++){
            int u,v;
            cin>>u>>v;
            graph[u].push_back(v);
            graph[v].push_back(u);
        }
        vector<int> vals(n,-1);
        for(int i=0;i<n;i++){
            vals[i]=i;
        }
        HLD *hld=new HLD(graph,vals);
        hld->print();
        int q;
        cin>>q;
        for(int i=0;i<q;i++){
            int u,v;
            cin>>u>>v;
            
            int ans=hld->query(u,v);
            cout<<u<<" , "<<v<<" : ";
            cout<<ans<<endl;
        }
        delete hld;
    }
};
