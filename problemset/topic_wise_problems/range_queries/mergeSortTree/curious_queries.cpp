// problem link : https://www.codingninjas.com/studio/contests/monthly-contest-17/9286791/problems/24492
// solution : below code 
#define ll long long
#define vi vector<ll>
#define pii pair<ll,ll>
const int MAX=5e5+100;
vector<pii> mstree[MAX];
class MergeSortSumTree {
public:
    vector<ll> arr;

    // vector<vector<pii>> mstree;
    ll n;
    ll len;
    MergeSortSumTree(vector<ll> & arr) {
        this->arr = arr;
        this->n = arr.size();
        // this->len=4*n;
        // mstree.resize(len);
        build(0, 0, n - 1);
    }
    void build(ll si, ll ss, ll se) {
        if (ss == se) {
            mstree[si] = {make_pair(arr[ss],arr[ss])};
            return;
        }
        ll mid = (ss + se) / 2;
        ll lefti = 2 * si + 1;
        ll righti = 2 * si + 2;
        build(lefti, ss, mid);
        build(righti, mid + 1, se);
        vector<pii> & left_arr = mstree[lefti];
        vector<pii> & right_arr = mstree[righti];
        mymerge(left_arr,right_arr,mstree[si]);

    }
    static void mymerge(vector<pii> & a, vector<pii> & b, vector<pii> & c) {
        ll az = a.size();
        ll bz = b.size();
        ll sz = az + bz;
        c.resize(sz);
        merge(a.begin(),a.end(),b.begin(),b.end(),c.begin());
        for(int i=0;i<sz;i++){
            c[i].second=c[i].first;
            if(i-1>=0){
                c[i].second+=c[i-1].second;
            }
        }
        return;
        
    }
    ll query(ll si, ll ss, ll se, ll qs, ll qe, ll k) {
        if (ss > qe || se < qs) return 0;
        if (ss >= qs && se <= qe) {
            ll ctr = 0;
            // do some stuff
            vector<pii> & row = mstree[si];
            // ctr=upper_bound(row.begin(),row.end(),k-1)-row.begin();
            ll sz = row.size();
            ll index = 0;
            pii pr={k+1,0};
            index=lower_bound(row.begin(), row.end(), pr) - row.begin();
            if(index>=sz) return 0;
            ctr = row[sz-1].second-row[index].second+row[index].first;
            return ctr;
        }

        ll mid = (ss + se) / 2;
        ll lefti = 2 * si + 1;
        ll righti = 2 * si + 2;

        ll l = query(lefti, ss, mid, qs, qe, k);
        ll r = query(righti, mid + 1, se, qs, qe, k);
        ll ctr = l + r;
        // check for change
        return ctr;
    }
    ll query(ll l, ll r, ll k) {
        return query(0, 0, n - 1, l, r, k);
    }
};
vector<long long> curiousQueries(int n, vector<int> &a, int q, vector<vector<int>> &queries) {
    vector<ll> a1(n);
    for(int i=0;i<n;i++){
        a1[i]=a[i];
    }
    MergeSortSumTree *mst=new MergeSortSumTree(a1);
    vector<ll> v;
    for(auto & row:queries){
        int l=0;
        int r=row[0];
        int b=row[1];
        int x=a1[b];
        ll ctr=mst->query(l,r,x);
        v.push_back(ctr);
    }
    return v;
}
