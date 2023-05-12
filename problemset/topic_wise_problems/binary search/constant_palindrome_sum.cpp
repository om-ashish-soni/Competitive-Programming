// problem link : https://codeforces.com/problemset/problem/1343/D
// solution : below code

#include<bits/stdc++.h>
using namespace std;

using ll = long long;
void solve(int t) {
    int n, k;
    cin >> n >> k;

    vector<int> v(n);
    for (int i = 0; i < n; i++) {
        cin >> v[i];
    }

    map<int, int> mp;
    vector<int> smaller;
    vector<int> bigger;

    for (int i = 0; i < (n + 1) / 2; i++) {
        int first = v[i];
        int second = v[n - i - 1];
        mp[first + second]++;
        smaller.push_back(min(first, second));
        bigger.push_back(k + max(first, second));
    }

    sort(smaller.begin(), smaller.end());
    sort(bigger.begin(), bigger.end());

    int mx = 0;
    int total = (n + 1) / 2;
    for (auto& pr : mp) {
        int key = pr.first;
        int freq = pr.second;
        int index1 = lower_bound(smaller.begin(), smaller.end(), key) - smaller.begin();
        int index2 = lower_bound(bigger.begin(), bigger.end(), key) - bigger.begin();
        int sz = smaller.size();
        int cut = (sz - index1) + index2;
        mx = max(mx, freq - cut);
    }
    int ctr = total - mx;
    cout << ctr << endl;
}

    



int main() {
    long long t;
    cin >> t;
    // t=1;
    for (long long i = 1; i <= t; i++) {
        solve(i);
    }
    return 0;
}
