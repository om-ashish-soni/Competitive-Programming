// problem link : https://cses.fi/problemset/task/1144/
// solution : code

#include<bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define int long long

#include <bits/stdc++.h>
using namespace std;
using namespace __gnu_pbds;

template <class T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

void solve(int testcase) {
    int n, q;
    cin >> n >> q;
    vector<int> v(n);

    for (int i = 0; i < n; i++) {
        cin >> v[i];
    }

    ordered_set<pair<int, int>> s;

    for (int i = 0; i < n; i++) {
        s.insert({v[i], i});
    }

    for (int i = 0; i < q; i++) {
        char type;
        cin >> type;

        if (type == '?') {
            int a, b;
            cin >> a >> b;

            pair<int, int> lpr = {a, -1};
            pair<int, int> rpr = {b + 1, -1};

            int left = s.order_of_key(lpr);
            int right = s.order_of_key(rpr);

            int ctr = right - left;
            cout << ctr << endl;
        } else {
            int index, value;
            cin >> index >> value;
            index--;

            s.erase({v[index], index});
            v[index] = value;
            s.insert({v[index], index});
        }
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
