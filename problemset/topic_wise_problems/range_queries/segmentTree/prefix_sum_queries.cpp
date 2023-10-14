// problem link : 

// explaination 

/*
* This code provides a solution to the "Prefix Sum Queries" problem from the CSES Problem Set. The problem involves processing a series of queries on an array of integers. There are two types of queries:

1. **Update**: Change the value of a specific element in the array.

2. **Query**: Find the maximum prefix sum within a given range [a, b] of the array.

To efficiently handle these queries, the code employs two critical data structures:

1. **Max Lazy Segment Tree**: This data structure facilitates range updates and queries efficiently. It allows for updates within a specified range and can find the maximum prefix sum in a given range.

2. **Fenwick Tree (Binary Indexed Tree)**: The Fenwick Tree maintains prefix sums of the array. It supports fast updates of individual array elements and can retrieve prefix sums quickly for queries.

The code reads the input, updates the data structures accordingly, and provides the output for each query. In the case of query type 2, it calculates and prints the maximum prefix sum within the specified range [a, b].

In summary, this code offers an efficient solution to the "Prefix Sum Queries" problem by using Max Lazy Segment Tree and Fenwick Tree to manage updates and queries on an array of integers.
*/

// solution : below code

#include<bits/stdc++.h>

#define int long long

class MaxLazySegmentTree {
private:
    int n = 0;
    int MYSIZE = 0;
    std::vector<long long> tree, lazy, arr;

public:
    MaxLazySegmentTree(std::vector<int>& v) {
        n = v.size();
        init(n);
        for (int i = 0; i < n; i++) {
            arr[i] = v[i];
        }
        post_init();
    }

    MaxLazySegmentTree(int v[], int n) {
        init(n);
        for (int i = 0; i < n; i++) {
            arr[i] = v[i];
        }
        post_init();
    }

    MaxLazySegmentTree(int n) {
        init(n);
        post_init();
    }

    void update(int us, int ue, int diff) {
        updateRangeUtil(0, 0, n - 1, us, ue, diff);
    }

    int query(int qs, int qe) {
        if (qs < 0 || qe > n - 1 || qs > qe) {
            std::cout << "Invalid Input" << std::endl;
            return -1;
        }
        return queryUtil(0, n - 1, qs, qe, 0);
    }

private:
    void init(int n) {
        this->n = n;
        MYSIZE = 4 * n + 10;
        tree.assign(MYSIZE, LLONG_MIN);
        lazy.assign(MYSIZE, 0LL);
        arr.assign(MYSIZE, 0LL);
    }

    void post_init() {
        constructST();
    }

    void updateRangeUtil(int si, int ss, int se, int us, int ue, int diff) {
        if (lazy[si] != 0) {
            tree[si] += lazy[si];
            if (ss != se) {
                lazy[si * 2 + 1] += lazy[si];
                lazy[si * 2 + 2] += lazy[si];
            }
            lazy[si] = 0;
        }
        if (ss > se || ss > ue || se < us)
            return;
        if (ss >= us && se <= ue) {
            tree[si] += diff;
            if (ss != se) {
                lazy[si * 2 + 1] += diff;
                lazy[si * 2 + 2] += diff;
            }
            return;
        }
        int mid = (ss + se) / 2;
        updateRangeUtil(si * 2 + 1, ss, mid, us, ue, diff);
        updateRangeUtil(si * 2 + 2, mid + 1, se, us, ue, diff);
        tree[si] = std::max(tree[si * 2 + 1], tree[si * 2 + 2]);
    }

    int queryUtil(int ss, int se, int qs, int qe, int si) {
        if (lazy[si] != 0) {
            tree[si] += lazy[si];
            if (ss != se) {
                lazy[si * 2 + 1] += lazy[si];
                lazy[si * 2 + 2] += lazy[si];
            }
            lazy[si] = 0;
        }
        if (ss > se || ss > qe || se < qs)
            return LLONG_MIN;
        if (ss >= qs && se <= qe)
            return tree[si];
        int mid = (ss + se) / 2;
        return std::max(queryUtil(ss, mid, qs, qe, 2 * si + 1),
                        queryUtil(mid + 1, se, qs, qe, 2 * si + 2));
    }

    void constructSTUtil(int ss, int se, int si) {
        if (ss > se)
            return;
        if (ss == se) {
            tree[si] = arr[ss];
            return;
        }
        int mid = (ss + se) / 2;
        if (ss <= mid)
            constructSTUtil(ss, mid, si * 2 + 1);
        if (mid + 1 <= se)
            constructSTUtil(mid + 1, se, si * 2 + 2);
        tree[si] = std::max(tree[si * 2 + 1], tree[si * 2 + 2]);
    }

    void constructST() {
        constructSTUtil(0, n - 1, 0);
    }
};

class FenwickTree {
private:
    std::vector<int> BIT;
    int n;

public:
    FenwickTree(int n) {
        this->n = n;
        BIT.assign(n, 0);
    }

    FenwickTree(int *arr, int n) {
        this->n = n;
        BIT.assign(n, 0);
        BIT[0] = arr[0];
        for (int i = 1; i < n; i++) {
            this->update(i, arr[i]);
        }
    }

    FenwickTree(std::vector<int>& v) {
        this->n = v.size();
        BIT.assign(n, 0);
        BIT[0] = v[0];
        for (int i = 1; i < n; i++) {
            this->update(i, v[i]);
        }
    }

    void update(int index, int delta) {
        if (index == 0) {
            BIT[index] += delta;
            return;
        }
        for (; index < n; index += index & -index)
            BIT[index] += delta;
    }

    int get(int index) {
        int sum = BIT[0];
        for (; index > 0; index -= index & -index)
            sum += BIT[index];
        return sum;
    }

    void print() {
        for (int i = 0; i < n; i++) {
            std::cout << BIT[i] << " ";
        }
        std::cout << std::endl;
    }
};

namespace solution {
    void solve(int testcase) {
        int n, m;
        std::cin >> n >> m;
        std::vector<int> v(n);

        for (int i = 0; i < n; i++) {
            std::cin >> v[i];
        }
        std::vector<int> pref = v;
        for (int i = 1; i < n; i++) {
            pref[i] += pref[i - 1];
        }

        MaxLazySegmentTree lst(pref);
        FenwickTree fnt(v);

        for (int i = 0; i < m; i++) {
            int type;
            std::cin >> type;
            if (type == 2) {
                int l, r;
                std::cin >> l >> r;
                l--;
                r--;
                int org = lst.query(l, r);
                if (l - 1 >= 0) {
                    org -= fnt.get(l - 1);
                }
                int ans = std::max(org, 0LL);
                std::cout << ans << std::endl;
            } else {
                int index, value;
                std::cin >> index >> value;
                index--;
                int delta = value - v[index];
                v[index] += delta;
                lst.update(index, n - 1, delta);
                fnt.update(index, delta);
            }
        }
    }
};

signed main(){
    solution::solve(0);
    return 0;
}