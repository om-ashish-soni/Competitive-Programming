// problem link : https://codeforces.com/problemset/problem/1395/C
// solution : below code

#include<bits/stdc++.h>
using namespace std;

using ll = long long;

void solve(int t) {
    int n, m;
    cin >> n >> m;

    vector<int> a(n);
    vector<int> b(m);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    for (int i = 0; i < m; i++) {
        cin >> b[i];
    }

    int sm = 0;
    vector<pair<int, int>> v;
    for (int k = 0; k < n; k++) {
        int mx = 0;
        int mx_index = 0;
        for (int i = 0; i < n; i++) {
            int mn = a[i];
            for (int j = 0; j < m; j++) {
                mn = min(mn, a[i] & b[j]);
            }
            v.push_back({mn, i});
            if (mx < mn) {
                mx = mn;
                mx_index = i;
            }
        }
        for (int i = 0; i < n; i++) {
            a[i] = a[i] & (~mx);
        }
        for (int j = 0; j < m; j++) {
            b[j] = b[j] & (~mx);
        }
        sm |= mx;
    }
    cout << sm << endl;
}




int main() {
    long long t;
    // cin >> t;
    t=1;
    for (long long i = 1; i <= t; i++) {
        solve(i);
    }
    return 0;
}
