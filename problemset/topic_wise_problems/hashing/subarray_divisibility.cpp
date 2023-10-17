// problem link : https://cses.fi/problemset/task/1662/
// solution : below code

void solve(int testcase) {
    int n;
    cin >> n; // Using cin for input
    vector<int> v(n);

    for (int i = 0; i < n; i++) {
        cin >> v[i];
    }

    map<int, int> mp;
    mp[0] = 1;
    int sm = 0;
    int ctr = 0;

    for (int i = 0; i < n; i++) {
        sm = ((sm + v[i]) % n + n) % n;
        if (mp.count(sm)) {
            // cout << "for sm: " << sm << " , adding: " << mp[sm] << endl;
            ctr += mp[sm];
        }
        mp[sm]++;
    }

    cout << ctr << endl; // Using cout for output
}
