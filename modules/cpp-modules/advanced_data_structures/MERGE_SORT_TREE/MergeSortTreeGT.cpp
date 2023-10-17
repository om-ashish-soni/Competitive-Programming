class MergeSortTree {
public:
    vector<int> arr;
    

    vector<vector<int>> mstree;
    int n;
    int len;
    MergeSortTree(vector<int> & arr) {
        this->arr = arr;
        this->n = arr.size();
        this->len=4*n;
        mstree.resize(len);
        build(0, 0, n - 1);
    }
    void build(int si, int ss, int se) {
        if (ss == se) {
            mstree[si] = {arr[ss]};
            return;
        }
        int mid = (ss + se) / 2;
        int lefti = 2 * si + 1;
        int righti = 2 * si + 2;
        build(lefti, ss, mid);
        build(righti, mid + 1, se);
        vector<int> & left_arr = mstree[lefti];
        vector<int> & right_arr = mstree[righti];
        mymerge(left_arr,right_arr,mstree[si]);

    }
    static void mymerge(vector<int> & a, vector<int> & b, vector<int> & c) {
        int az = a.size();
        int bz = b.size();
        int sz = az + bz;
        c.resize(sz);
        merge(a.begin(),a.end(),b.begin(),b.end(),c.begin());
        return;
        
    }
    int query(int si, int ss, int se, int qs, int qe, int k) {
        if (ss > qe || se < qs) return 0;
        if (ss >= qs && se <= qe) {
            int ctr = 0;
            // do some stuff
            vector<int> & row = mstree[si];
            // ctr=upper_bound(row.begin(),row.end(),k-1)-row.begin();
            int sz = row.size();
            int index = upper_bound(row.begin(), row.end(), k) - row.begin();
            ctr = sz - index;
            return ctr;
        }

        int mid = (ss + se) / 2;
        int lefti = 2 * si + 1;
        int righti = 2 * si + 2;

        int l = query(lefti, ss, mid, qs, qe, k);
        int r = query(righti, mid + 1, se, qs, qe, k);
        int ctr = l + r;
        // check for change
        return ctr;
    }
    int query(int l, int r, int k) {
        return query(0, 0, n - 1, l, r, k);
    }
};
