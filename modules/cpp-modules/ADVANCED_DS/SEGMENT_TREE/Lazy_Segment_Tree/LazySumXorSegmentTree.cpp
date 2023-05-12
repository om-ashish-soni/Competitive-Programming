class LazySumXorSegmentTree{
    int n=0;
    int MYSIZE=0;
    vector<long long> tree;
    vector<bool> lazy;
    vector<long long> arr;
    public:
    void init(int n){
        this->n=n;
        this->MYSIZE=4*n+10;
        tree.assign(MYSIZE,0LL);
        lazy.assign(MYSIZE,false);
        arr.assign(MYSIZE,0LL);
    }
    void post_init(){
        this->constructST();
    }
    LazySumXorSegmentTree(vector<int> & v){
        int n=v.size();
        init(n);
        for(int i=0;i<n;i++){
            arr[i]=v[i];
        }
        post_init();
    }
    LazySumXorSegmentTree(int v[],int n){
        init(n);
        for(int i=0;i<n;i++){
            arr[i]=v[i];
        }
        post_init();
    }
    LazySumXorSegmentTree(int n){
        init(n);
        post_init();
    }
    void updateRangeUtil(int si, int ss, int se, int us,
                         int ue, int diff)
    {
        if (lazy[si])
        {
            tree[si] = ((se-ss+1)-tree[si]);
            if (ss != se)
            {
                lazy[si*2 + 1]   = !lazy[si*2 + 1];
                lazy[si*2 + 2]   = !lazy[si*2 + 2];
            }
            lazy[si] = false;
        }
        if (ss>se || ss>ue || se<us)
            return ;
        if (ss>=us && se<=ue)
        {
            tree[si] = ((se-ss+1)-tree[si]);
            if (ss != se)
            {
                lazy[si*2 + 1]   = !lazy[si*2 + 1];
                lazy[si*2 + 2]   = !lazy[si*2 + 2];
            }
            return;
        }
        int mid = (ss+se)/2;
        updateRangeUtil(si*2+1, ss, mid, us, ue, diff);
        updateRangeUtil(si*2+2, mid+1, se, us, ue, diff);
        tree[si] = tree[si*2+1] + tree[si*2+2];
    }
    void updateRange(int us, int ue, int diff)
    {
       updateRangeUtil(0, 0, n-1, us, ue, diff);
    }
    void update(int us,int ue,int diff){
        updateRange(us,ue,diff);
    }
    int getSumUtil(int ss, int se, int qs, int qe, int si)
    {
        if (lazy[si])
        {
            tree[si] = ((se-ss+1)-tree[si]);
            if (ss != se)
            {
                lazy[si*2 + 1]   = !lazy[si*2 + 1];
                lazy[si*2 + 2]   = !lazy[si*2 + 2];
            }
            lazy[si] = false;
        }
        if (ss>se || ss>qe || se<qs)
            return 0;
        if (ss>=qs && se<=qe)
            return tree[si];
        int mid = (ss + se)/2;
        return getSumUtil(ss, mid, qs, qe, 2*si+1) +
               getSumUtil(mid+1, se, qs, qe, 2*si+2);
    }
    int getSum(int qs, int qe)
    {
        if (qs < 0 || qe > n-1 || qs > qe)
        {
            printf("Invalid Input");
            return -1;
        }
        return getSumUtil(0, n-1, qs, qe, 0);
    }
    int query(int qs,int qe){
        return getSum(qs,qe);
    }
    void constructSTUtil(int ss, int se, int si)
    {
        if (ss > se)
            return ;
        if (ss == se){
            tree[si] = arr[ss];
            return;
        }
        int mid = (ss + se)/2;
        if(ss<=mid) constructSTUtil(ss, mid, si*2+1);
        if(mid+1<=se) constructSTUtil(mid+1, se, si*2+2);
        tree[si] = tree[si*2 + 1] + tree[si*2 + 2];
    }
    void constructST(){
        constructSTUtil(0, n-1, 0);
    }

    static void how_to_use(){
        vector<int> bits={1,1,0,1,1};
        LazySumXorSegmentTree *lsxt=new LazySumXorSegmentTree(bits);
        lsxt->update(1,2,1);
        int ans=lsxt->query(2,2);
        cout<<ans<<endl;
        delete lsxt;
    }
};