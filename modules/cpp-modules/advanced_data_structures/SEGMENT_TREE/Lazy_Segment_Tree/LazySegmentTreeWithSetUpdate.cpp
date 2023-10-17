#include<bits/stdc++.h>
#define int long long
using namespace std;

class LazySegmentTreeWithSetUpdate{
    int n=0;
    int MYSIZE=0;
    vector<long long> tree,lazy,stamp;
    vector<bool> pending;
    vector<long long> arr;
    int tm=0;
    public:
    void init(int n){
        this->n=n;
        this->MYSIZE=4*n+10;
        tree.assign(MYSIZE,0LL);
        lazy.assign(MYSIZE,0LL);
        arr.assign(MYSIZE,0LL);
        stamp.assign(MYSIZE,0LL);
        pending.assign(MYSIZE,false);
    }
    void post_init(){
        this->constructST();
    }
    LazySegmentTreeWithSetUpdate(vector<int> & v){
        int n=v.size();
        init(n);
        for(int i=0;i<n;i++){
            arr[i]=v[i];
        }
        post_init();
    }
    LazySegmentTreeWithSetUpdate(int v[],int n){
        init(n);
        for(int i=0;i<n;i++){
            arr[i]=v[i];
        }
        post_init();
    }
    LazySegmentTreeWithSetUpdate(int n){
        init(n);
        post_init();
    }
    void updateRangeUtil(int si, int ss, int se, int us,
                         int ue, int diff,int stamp_value)
    {
        if (pending[si])
        {
            tree[si] = (se-ss+1)*lazy[si];
            if (ss != se)
            {
                if(stamp[si*2+1]<=stamp[si]){
                    lazy[si*2 + 1]   = lazy[si];
                    stamp[si*2 + 1]   = stamp[si];
                    pending[si*2+1]=true;
                }
                if(stamp[si*2+2]<=stamp[si]){
                    lazy[si*2 + 2]   = lazy[si];    
                    stamp[si*2 + 2]   = stamp[si];
                    pending[si*2+2]=true;
                }
            }
            pending[si]=false;
        }
        if (ss>se || ss>ue || se<us)
            return ;
        if (ss>=us && se<=ue)
        {
            tree[si] = (se-ss+1)*diff;
            if (ss != se)
            {
                if(stamp[si*2+1]<=stamp_value){
                    lazy[si*2 + 1]   = diff;
                    stamp[si*2 + 1]   = stamp_value;
                    pending[si*2+1]=true;
                }
                if(stamp[si*2+2]<=stamp_value){
                    lazy[si*2 + 2]   = diff;    
                    stamp[si*2 + 2]   = stamp_value;
                    pending[si*2+2]=true;
                }
            }
            stamp[si]=stamp_value;
            return;
        }
        int mid = (ss+se)/2;
        updateRangeUtil(si*2+1, ss, mid, us, ue, diff,stamp_value);
        updateRangeUtil(si*2+2, mid+1, se, us, ue, diff,stamp_value);
        tree[si] = tree[si*2+1] + tree[si*2+2];
    }
    void updateRange(int us, int ue, int diff)
    {
       ++tm;
       updateRangeUtil(0, 0, n-1, us, ue, diff,tm);
    }
    void update(int us,int ue,int diff){
        updateRange(us,ue,diff);
    }
    int getSumUtil(int ss, int se, int qs, int qe, int si)
    {
        if (pending[si])
        {

            tree[si] = (se-ss+1)*lazy[si];
            if (ss != se)
            {
                if(stamp[si*2+1]<=stamp[si]){
                    lazy[si*2+1] = lazy[si];
                    stamp[si*2+1]=stamp[si]; 
                    pending[si*2+1]=true;   
                }
                if(stamp[si*2+2]<=stamp[si]){
                    lazy[si*2+2] = lazy[si];
                    stamp[si*2+2]=stamp[si];    
                    pending[si*2+2]=true;
                }
            }
            pending[si]=false;
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
        vector<int> arr={1,2,3,4};
        LazySegmentTreeWithSetUpdate *mylst=new LazySegmentTreeWithSetUpdate(arr);
        mylst->update(0,3,0);
        mylst->update(2,3,2);
        mylst->update(0,2,10);
        int ans=mylst->query(1,2);
        cout<<ans<<endl;
    }
};

signed main(){
	vector<int> arr={1,2,3,4};
    LazySegmentTreeWithSetUpdate *mylst=new LazySegmentTreeWithSetUpdate(arr);
    mylst->update(0,3,0);
    cout<<"updating range from "<<0<<" to "<<3<<" with value : "<<0<<endl;
    mylst->update(2,3,2);
    cout<<"updating range from "<<2<<" to "<<3<<" with value : "<<2<<endl;
    mylst->update(0,2,10);
    cout<<"updating range from "<<0<<" to "<<2<<" with value : "<<10<<endl;
    int ans=mylst->query(1,2);
    cout<<"sum in range : "<<1<<" to "<<2<<" : "<<ans<<endl;
	return 0;
}