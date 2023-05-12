// problem link : https://www.hackerearth.com/practice/algorithms/searching/linear-search/practice-problems/algorithm/special-shop-69904c91/
// solution : below code

#include <bits/stdc++.h>
using namespace std;
int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        long n, a, b;
        cin >> n >> a >> b;
        double x = (double)(n * b) / (double)(a + b);
        long x1 = floor(x);
        long x2 = ceil(x);
        // cout<<x1<<" "<<x2<<endl;
        long ans1 = (a * (x1 * x1) + b * (n - x1) * (n - x1));
        long ans2 = (a * (x2 * x2) + b * (n - x2) * (n - x2));

        cout << min(ans1, ans2) << endl;
    }
    return 0;
}