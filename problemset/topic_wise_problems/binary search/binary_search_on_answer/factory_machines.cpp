// problem link : https://cses.fi/problemset/task/1620/
// solution : below code

#include<bits/stdc++.h>
using namespace std;
#define int long long

void solve(int testcase) {
    int n, x;
    cin >> n >> x;
    vector<int> v(n);

    for (int i = 0; i < n; i++) {
        cin >> v[i];
    }

    int l = 0;
    int r = x * (*min_element(v.begin(), v.end()));
    int mn = r;

    while (l <= r) {
        int mid = l + (r - l) / 2;
        int comp = 0;

        for (int num : v) {
            comp += mid / num;
        }

        if (comp >= x) {
            mn = min(mn, mid);
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }


    cout << mn << endl;
}



signed main() {
    int t=1;
    // cin >> t;

    for (int i = 1; i <= t; ++i) {
        solve(i);
    }

    return 0;
}
