#include <bits/stdc++.h>
using namespace std;
int kthRoot(int n, int k)
{
    int l = 0;
    int r = n;
    int ans = 0;
    while (l <= r)
    {
        int mid = l + (r - l) / 2;
        if (pow(mid, k) > n)
        {
            r = mid - 1;
        }
        else
        {
            ans = mid;
            l = mid + 1;
        }
    }
    return ans;
}