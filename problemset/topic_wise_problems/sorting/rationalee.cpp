// problem link : https://codeforces.com/problemset/problem/1369/C
// solution : below code

#include <bits/stdc++.h>
#define int long long
using namespace std;

void solve(int t)
{
    int n, m;
    cin >> n >> m;
    vector<int> arr(n);
    for (int i = 0; i < n; i++)
        cin >> arr[i];
    vector<int> mitra(m);
    for (int i = 0; i < m; i++)
        cin >> mitra[i];

    sort(arr.begin(), arr.end());
    reverse(arr.begin(), arr.end());
    sort(mitra.begin(), mitra.end());
    vector<pair<int, int>> dp(m, {0, 0});
    int score = 0;
    int index = 0;
    for (int i = 0; i < m; i++)
    {
        dp[i] = {arr[index], arr[index]};
        mitra[i]--;
        index++;
    }
    for (int i = 0; i < m; i++)
    {
        if (mitra[i] == 0)
            continue;
        dp[i].second = arr[index + mitra[i] - 1];
        index += mitra[i];
    }
    for (int i = 0; i < m; i++)
    {
        score += dp[i].second + dp[i].first;
    }
    cout << score << endl;
}

signed main()
{
    int t = 1;
    cin >> t; // testcase
    while (t--)
    {
        solve(t);
    }
    return 0;
}