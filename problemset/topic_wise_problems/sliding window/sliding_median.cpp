// problem link : https://cses.fi/problemset/task/1620/
// solution : below code

#include<bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define int long long

void solve(int testcase) {
    int n, k;
    cin >> n >> k;
    vector<int> v(n);

    for (int i = 0; i < n; i++) {
        cin >> v[i];
    }

    int order = (k - 1) / 2;

    tree<pair<int, int>, null_type, less<pair<int, int>>, rb_tree_tag, tree_order_statistics_node_update> s;

    for (int i = 0; i < k; i++) {
        s.insert({v[i], i});
    }

    for (int i = k - 1; i < n; i++) {
        s.insert({v[i], i});

        pair<int, int> elem = *s.find_by_order(order);

        s.erase({v[i - k + 1], i - k + 1});

        cout << elem.first << " ";
    }
}



signed main() {
    int t=1;
    // cin >> t;

    for (int i = 1; i <= t; ++i) {
        solve(i);
    }

    return 0;
}
