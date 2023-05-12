// problem link : https://codeforces.com/problemset/problem/1537/D
// solution : below code

#include <bits/stdc++.h>
#define int long long
using namespace std;

bool isPowerOfTwo(int n)
{
    bitset<32> bs(n);
    return bs.count() == 1;
}
bool isBob(int n)
{
    if (n % 2)
        return true;
    if (isPowerOfTwo(n))
    {
        int l2 = log2(n);
        return (l2 % 2);
    }
    return false;
}
void solve(int t)
{
    int n;
    cin >> n;
    if (isBob(n))
        cout << "Bob";
    else
        cout << "Alice";
    cout << endl;
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