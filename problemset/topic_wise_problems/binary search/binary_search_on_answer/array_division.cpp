// problem link : https://cses.fi/problemset/task/1085/
// solution : below code

#include<bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define int long long
#define LOG_DEBUG false
using pii = pair<int, int>;
using vpii = vector<pii>;

void solve(int testcase) {
    int n, k;
    cin >> n >> k; // Using cin for input
    vector<int> v(n);

    for (int i = 0; i < n; i++) {
        cin >> v[i];
    }

    int l = *max_element(v.begin(), v.end());
    int r = accumulate(v.begin(), v.end(), 0LL);
    int mn = r;

    while (l <= r) {
        int mid = l + (r - l) / 2;
        int x = 1;
        int sm = 0;

        for (int i = 0; i < n; i++) {
            if (sm + v[i] > mid) {
                sm = 0;
                x++;
            }
            sm += v[i];
        }

        // cout << " for mid: " << mid << " , " << x << " vs " << k << endl;
        if (x <= k) {
            mn = min(mn, mid);
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }

    cout << mn << endl; // Using cout for output
}

signed main() {

    solve(0);

    return 0;
}



