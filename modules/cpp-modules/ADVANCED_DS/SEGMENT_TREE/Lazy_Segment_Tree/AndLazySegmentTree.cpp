class AndLazySegmentTree{
	int n=0;
	int MYSIZE=0;
	vector<long long> tree,lazy;
	vector<long long> arr;
	public:
	void init(int n){
		this->n=n;
		this->MYSIZE=4*n+10;
		tree.assign(MYSIZE,LLONG_MAX);
		lazy.assign(MYSIZE,LLONG_MAX);
		arr.assign(MYSIZE,LLONG_MAX);
	}
	void post_init(){
		this->constructST();

	}
	AndLazySegmentTree(vector<int> & v){
		int n=v.size();
		init(n);
		for(int i=0;i<n;i++){
			arr[i]=v[i];
		}
		post_init();
	}
	AndLazySegmentTree(int v[],int n){
		init(n);
		for(int i=0;i<n;i++){
			arr[i]=v[i];
		}
		post_init();
	}
	AndLazySegmentTree(int n){
		init(n);
		post_init();
	}
	void updateRangeUtil(int si, int ss, int se, int us,
	                     int ue, int diff)
	{
		// cout<<"tree["<<si<<"] : "<<tree[si]<<endl;
	    if (lazy[si] != LLONG_MAX)
	    {
	        tree[si] &= lazy[si];
	        if (ss != se)
	        {
	            lazy[si*2 + 1]   &= lazy[si];
	            lazy[si*2 + 2]   &= lazy[si];
	        }
	        lazy[si] = LLONG_MAX;
	    }
	    if (ss>se || ss>ue || se<us)
	        return ;
	    if (ss>=us && se<=ue)
	    {
	        tree[si] &= diff;
	        if (ss != se)
	        {
	            lazy[si*2 + 1]   &= diff;
	            lazy[si*2 + 2]   &= diff;
	        }
	        return;
	    }
	    int mid = (ss+se)/2;
	    updateRangeUtil(si*2+1, ss, mid, us, ue, diff);
	    updateRangeUtil(si*2+2, mid+1, se, us, ue, diff);
	    tree[si] = tree[si*2+1] & tree[si*2+2];
	    // cout<<"tree["<<si<<"] : "<<tree[si]<<endl;

	}
	void updateRange(int us, int ue, int diff)
	{
	   updateRangeUtil(0, 0, n-1, us, ue, diff);
	}
	  
	  
	int getRangeUtil(int ss, int se, int qs, int qe, int si)
	{
	    if (lazy[si] != LLONG_MAX)
	    {
	        tree[si] &= lazy[si];
	        if (ss != se)
	        {
	            lazy[si*2+1] &= lazy[si];
	            lazy[si*2+2] &= lazy[si];
	        }
	        lazy[si] = LLONG_MAX;
	    }
	    if (ss>se || ss>qe || se<qs)
	        return LLONG_MAX;
	    if (ss>=qs && se<=qe)
	        return tree[si];
	    int mid = (ss + se)/2;
	    return getRangeUtil(ss, mid, qs, qe, 2*si+1) &
	           getRangeUtil(mid+1, se, qs, qe, 2*si+2);
	}
	int getRange(int qs, int qe)
	{
	    if (qs < 0 || qe > n-1 || qs > qe)
	    {
	        printf("Invalid Input");
	        return -1;
	    }
	    return getRangeUtil(0, n-1, qs, qe, 0);
	}
	void constructSTUtil(int ss, int se, int si)
	{
		// cout<<"tree["<<si<<"] : "<<tree[si]<<endl;
	    if (ss > se)
	        return ;
	    if (ss == se){
	        tree[si] = arr[ss];
	        return;
	    }
	    int mid = (ss + se)/2;
	    if(ss<=mid) constructSTUtil(ss, mid, si*2+1);
	    if(mid+1<=se) constructSTUtil(mid+1, se, si*2+2);
	    tree[si] = (tree[si*2 + 1] & tree[si*2 + 2]);
	    // cout<<"tree["<<si<<"] : "<<tree[si]<<endl;
	}
	void constructST(){
	    constructSTUtil(0, n-1, 0);
	}
};