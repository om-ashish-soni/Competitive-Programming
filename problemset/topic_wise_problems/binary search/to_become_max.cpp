// problem link : https://codeforces.com/contest/1856/problem/C
// solution : below code

bool can(vi &v, int k, int target, int index)
{
    int n = v.size();
    if (index >= n)
        return false;
    if (v[index] >= target)
        return true;
    int delta = target - v[index];
    if (index >= n - 1 || k < delta)
        return false;

    return can(v, k - delta, target - 1, index + 1);
}
void solve(int testcase)
{

    int n, k;
    read(n, k);
    vi v(n);
    readv(v);

    int mx = 0;
    int mn = LLONG_MAX;
    FEACH(num, v)
    {
        mx = max(mx, num);
        mn = min(mn, num);
    }
    int l = mn;
    int r = mx + k;
    while (l <= r)
    {
        int mid = l + (r - l) / 2;
        bool flag = false;
        F(i, 0, n)
        {
            if (can(v, k, mid, i))
            {
                flag = true;
                break;
            }
        }
        if (flag)
        {
            mx = mid;
            l = mid + 1;
        }
        else
        {
            r = mid - 1;
        }
    }
    println(mx);
}