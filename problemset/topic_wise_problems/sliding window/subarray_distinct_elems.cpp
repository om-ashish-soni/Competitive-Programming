// problem link : https://cses.fi/problemset/task/2428/
// solution : below code

#include<bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define int long long
#define LOG_DEBUG false
using pii = pair<int, int>;
using vpii = vector<pii>;

void remove(map<int, int>& mp, int x) {
    int& freq = mp[x];
    freq--;
    if (freq <= 0) {
        mp.erase(x);
    }
}

int atMostKDistinct(vector<int>& nums, int k) {
    if (k == 0) {
        return 0;
    }

    map<int, int> mp;
    int n = nums.size();
    int l = 0;
    int ctr = 0;

    for (int i = 0; i < n; i++) {
        mp[nums[i]]++;
        while (l <= i && mp.size() > k) {
            remove(mp, nums[l]);
            l++;
        }

        int r = i;
        int delta = (r - l + 1);
        ctr += delta;
    }

    return ctr;
}

void solve(int testcase) {
    int n, k;
    cin >> n >> k; // Using cin for input
    vector<int> v(n);

    for (int i = 0; i < n; i++) {
        cin >> v[i];
    }

    cout << atMostKDistinct(v, k) << endl; // Using cout for output
}

signed main() {

    solve(0);

    return 0;
}



