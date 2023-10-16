// problem link : https://cses.fi/problemset/task/2169/
// solution : below code

#include<bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp> // Common file
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/detail/standard_policies.hpp>
using namespace __gnu_pbds;
using namespace std;
template <
    typename Key, // Key type
    typename Mapped, // Mapped-policy
    typename Cmp_Fn = std::less<Key>, // Key comparison functor
    typename Tag = rb_tree_tag, // Specifies which underlying data structure to use
    template <
        typename Const_Node_Iterator,
        typename Node_Iterator,
        typename Cmp_Fn_,
        typename Allocator_ >
    class Node_Update = null_node_update, // A policy for updating node invariants
    typename Allocator = std::allocator<char> > // An allocator type
class pbds_tree;
// typedef tree<int,null_type,less<int>,rb_tree_tag,tree_order_statistics_node_update> ordered_set;
template <class T> using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
template <class K, class V> using ordered_map = tree<K, V, less<K>, rb_tree_tag, tree_order_statistics_node_update>;

#define int long long
#include <bits/stdc++.h>
using namespace std;

#define pb push_back
#define all(x) (x).begin(), (x).end()

typedef pair<int, int> pii;
typedef vector<pair<pii, int>> vpii;

void solve(int testcase) {
    int n;
    cin >> n;

    vpii v(n);
    vector<int> v1(n, 0), v2(n, 0);

    for (int i = 0; i < n; ++i) {
        cin >> v[i].first.first >> v[i].first.second;
        v[i].first.second = -v[i].first.second;
        v[i].second = i;
    }

    sort(all(v));

    int mx_so_far = INT_MIN;
    int mx_index = -1;

    ordered_set<pii> s;

    for (int i = n - 1; i >= 0; --i) {
        int l = v[i].first.first;
        int r = -v[i].first.second;
        int index = v[i].second;

        pii pr = {r + 1, 0};
        int ord = s.order_of_key(pr);

        v1[index] = ord;
        s.insert({r, index});
    }

    s.clear();

    for (int i = 0; i < n; ++i) {
        int l = v[i].first.first;
        int r = v[i].first.second;
        int index = v[i].second;
        
        int ord = s.order_of_key({r + 1, 0});
        // cout << l << "," << r << " : " << ord << endl;
        v2[index] = ord;
        s.insert({r, index});
    }

    for (int i = 0; i < n; ++i) {
        cout << v1[i] << " ";
    }
    cout << endl;

    for (int i = 0; i < n; ++i) {
        cout << v2[i] << " ";
    }
    cout << endl;
}

signed main() {
    int t=1;
    // cin >> t;

    for (int i = 1; i <= t; ++i) {
        solve(i);
    }

    return 0;
}
