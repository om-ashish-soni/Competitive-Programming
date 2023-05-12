// problem link : https://www.hackerearth.com/practice/algorithms/searching/linear-search/practice-problems/algorithm/yet-another-easy-problem-1f3273a0/
// solution : below code

#include <bits/stdc++.h>
using namespace std;
int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        int l, r;
        cin >> l >> r;
        int ctr = 0;
        for (int num = l; num <= r; num++)
        {
            int temp = num;
            int sum = 0;
            while (temp > 0)
            {
                sum += temp % 16;
                temp /= 16;
            }
            // cout<<sum<<" "<<num<<endl;
            if (__gcd(sum, num) > 1)
                ctr++;
        }
        cout << ctr << endl;
    }
    return 0;
}