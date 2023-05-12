// problem link : https://www.codechef.com/problems/TAKENOTLESS?tab=statement
// solution : below code

#include<bits/stdc++.h>
using namespace std;
void solve(int t) {
    int n;
    cin >> n;
    vector<int> v(n);
    for (int i = 0; i < n; i++) {
        cin >> v[i];
    }
    sort(v.rbegin(), v.rend());
    bool flag = (n == 1);
    for (int i = 0; i < n; i++) {
        if (i % 2 == 0) {
            if (i + 1 < n && v[i] != v[i + 1]) {
                flag = true;
                break;
            }
        }
    }
    if (flag) {
        cout << "Marichka" << endl;
    } else {
        cout << "Zenyk" << endl;
    }
}

int main() {
    int t;
    cin >> t;
    for (int i = 1; i <= t; i++) {
        solve(i);
    }
    return 0;
}