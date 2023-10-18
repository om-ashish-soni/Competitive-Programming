// problem link : https://cses.fi/problemset/task/1629/
// solution : below code

#include<bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define int long long

void solve(int testcase) {
    int n;
    cin >> n;
    map<pair<int, int>, int> dp;

    for (int i = 0; i < n; ++i) {
        int x, y;
        cin >> x >> y;
        dp[{x, y}] = 1;
    }

    int last = 0;
    int mx = 0;

    for (auto it = dp.rbegin(); it != dp.rend(); ++it) {
        int l = (it->first).first;
        int r = (it->first).second;

        auto next = dp.lower_bound({r, -1});
        int next_score = (next != dp.end()) ? (next->second) : 0;

        it->second = max(1 + next_score, last);
        last = it->second;
        mx = max(mx, it->second);
    }

    cout << mx << endl;
}



signed main() {

    solve(0);

    return 0;
}



