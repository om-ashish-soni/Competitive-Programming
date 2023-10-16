// problem link : https://cses.fi/problemset/task/2168/
// solution : below code

#include<bits/stdc++.h>
using namespace std;


void solve(int testcase) {
    int n;
    cin >> n;
    
    vector<pair<pair<int, int>, int>> v(n);
    vector<int> v1(n, 0), v2(n, 0);

    for (int i = 0; i < n; ++i) {
        cin >> v[i].first.first;
        cin >> v[i].first.second;
        v[i].first.second = -v[i].first.second;
        v[i].second = i;
    }

    sort(v.begin(), v.end());

    int mx_so_far = INT_MIN;
    int mx_index = -1;

    for (int i = n - 1; i >= 0; --i) {
        int l = v[i].first.first;
        int r = v[i].first.second;
        int index = v[i].second;

        if (mx_so_far < r) {
            mx_so_far = r;
            mx_index = index;
        } else {
            v1[index] = 1;
        }
    }

    int mn_so_far = INT_MAX;
    int mn_index = -1;

    for (int i = 0; i < n; ++i) {
        int l = v[i].first.first;
        int r = v[i].first.second;
        int index = v[i].second;

        if (mn_so_far > r) {
            mn_so_far = r;
            mn_index = index;
        } else {
            v2[index] = 1;
        }
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
