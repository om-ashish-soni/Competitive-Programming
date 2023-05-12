// problem link : https://codeforces.com/problemset/problem/1519/D
// solution : below code
#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;

using ll = long long;
using vi = vector<long long>;
using vvi = vector<vi>;
using map = unordered_map<long long, long long>;

void solve(long long test_case){
    long long n;
    cin >> n;

    vi a(n);
    vi b(n);
    vi v(n);
    for (long long i = 0; i < n; i++) {
        cin >> a[i];
    }
    for (long long i = 0; i < n; i++) {
        cin >> b[i];
    }

    long long sum = 0;
    for (long long i = 0; i < n; i++) {
        v[i] = a[i] * b[i];
        sum += v[i];
    }

    vvi dp(n, vi(n, 0));
    long long max_diff_product = 0;
    for (long long diff = 1; diff < n; diff++) {
        for (long long i = 0; i < n - diff; i++) {
            long long left_index = i;
            long long right_index = i + diff;
            dp[left_index][right_index] = (a[right_index] - a[left_index]) * (b[left_index] - b[right_index]);

            if (left_index + 1 <= right_index - 1) {
                dp[left_index][right_index] += dp[left_index + 1][right_index - 1];
            }

            max_diff_product = max(max_diff_product, dp[left_index][right_index]);
        }
    }

    sum += max_diff_product;
    cout << sum << endl;
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
