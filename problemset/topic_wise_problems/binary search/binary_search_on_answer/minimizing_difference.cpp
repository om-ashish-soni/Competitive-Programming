// problem link : https://codeforces.com/contest/1244/problem/E
// solution : below code

#include<bits/stdc++.h>
using namespace std;
#define int long long

void solve(int testcase) {
    int n, k;
    cin >> n >> k;
    
    vector<int> v(n);
    for (int i = 0; i < n; ++i) {
        cin >> v[i];
    }
    sort(v.begin(), v.end());

    vector<int> pref = v;
    vector<int> suff = v;
    
    for (int i = 1; i < n; ++i) {
        pref[i] += pref[i - 1];
    }
    
    for (int i = n - 2; i >= 0; --i) {
        suff[i] += suff[i + 1];
    }

    int l = 0;
    int r = v.back() - v.front();
    int mn = r;

    while (l <= r) {
        int mid = l + (r - l) / 2;
        bool done = false;
        int d = mid;
        
        for (int i = 0; i < n; ++i) {
            int left_index = i - 1;
            int right_index = upper_bound(v.begin(), v.end(), v[i] + d) - v.begin();
            int actual_left = 0, actual_right = 0;
            int ideal_left = (left_index + 1) * v[i];
            int ideal_right = (n - right_index) * (v[i] + d);
            
            if (left_index >= 0) {
                actual_left = pref[left_index];
            }
            
            if (right_index < n) {
                actual_right = suff[right_index];
            }
            
            int ldiff = abs(actual_left - ideal_left);
            int rdiff = abs(actual_right - ideal_right);
            int delta = ldiff + rdiff;

            if (delta <= k) {
                done = true;
                break;
            }
        }

        if (done) {
            mn = min(mn, mid);
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }

    l = 0;
    r = v.back() - v.front();

    while (l <= r) {
        int mid = l + (r - l) / 2;
        bool done = false;
        int d = mid;
        
        for (int i = 0; i < n; ++i) {
            int right_index = i + 1;
            int left_index = lower_bound(v.begin(), v.end(), v[i] - d) - v.begin() - 1;
            int actual_left = 0, actual_right = 0;
            int ideal_left = (left_index + 1) * (v[i] - d);
            int ideal_right = (n - right_index) * v[i];
            
            if (left_index >= 0) {
                actual_left = pref[left_index];
            }
            
            if (right_index < n) {
                actual_right = suff[right_index];
            }
            
            int ldiff = abs(actual_left - ideal_left);
            int rdiff = abs(actual_right - ideal_right);
            int delta = ldiff + rdiff;

            if (delta <= k) {
                done = true;
                break;
            }
        }

        if (done) {
            mn = min(mn, mid);
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }

    cout << mn << endl;
}


signed main() {
    int t=1;
    // cin >> t;

    for (int i = 1; i <= t; ++i) {
        solve(i);
    }

    return 0;
}
