// problem link : https://codeforces.com/problemset/problem/1458/A
// solution : below code

#include <bits/stdc++.h>
#define int long long
using namespace std;

void findAllFactors(int n, std::vector<int> &factors)
{
    if (n == 0)
        return;
    double sqroot = sqrt(n);
    factors.push_back(1);
    if (n == 1)
    {
        return;
    }
    for (int i = 2; i <= sqroot; i++)
    {
        if (n % i == 0)
        {
            factors.push_back(i);
            if (n / i != i)
            {
                factors.push_back(n / i);
            }
        }
    }
    factors.push_back(n);
    sort(factors.begin(), factors.end());
}

void solve(int t)
{
    int n, m;
    cin >> n >> m;
    vector<int> a(n), b(m);
    for (int i = 0; i < n; i++)
        cin >> a[i];
    for (int j = 0; j < m; j++)
        cin >> b[j];

    int root_hcf = 0;
    for (int i = 1; i < n; i++)
    {
        int delta = abs(a[i] - a[i - 1]);
        root_hcf = __gcd(root_hcf, delta);
    }
    for (int i = 0; i < m; i++)
    {
        int ans = __gcd(root_hcf, a.front() + b[i]);
        cout << ans << " ";
    }
    cout << endl;
}

signed main()
{
    int t = 1;
    // cin >> t; // testcase
    while (t--)
    {
        solve(t);
    }
    return 0;
}