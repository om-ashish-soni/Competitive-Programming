// problem link : https://codeforces.com/contest/484/problem/B
// solution : below code

#include<bits/stdc++.h>
using namespace std;
#define int long long

namespace Solution {
    void solve(int t) {
        int n;
        cin >> n;
        vector<int> a(n);
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }

        set<int> s(a.begin(), a.end());
        s.erase(1);
        a.assign(s.begin(), s.end());
        int limit = a.back() + 10;
        n = a.size();
        int mx = 0;
        for (int i = 0; i < n; i++) {
            int num = a[i];
            int index = i + 1;
            for (int j = num + num; index < n; j += num) {
                index = lower_bound(a.begin() + index, a.end(), j) - a.begin();
                if (index - 1 >= 0) {
                    int curr = a[index - 1] % num;
                    mx = max(mx, curr);
                }
            }
        }
        cout << mx << endl;
    }
}



signed main() {
    long long t;
    // cin >> t;
    t=1;
    for (long long i = 1; i <= t; i++) {
        Solution::solve(i);
    }
    return 0;
}

