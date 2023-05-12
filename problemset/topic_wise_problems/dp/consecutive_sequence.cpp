// problem link : https://codeforces.com/problemset/problem/977/F
// solution : below code

#include<bits/stdc++.h>
#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;

using ll = long long;
using vi = vector<long long>;
using vvi = vector<vi>;
using map = unordered_map<long long, long long>;

void solve(int test_case) {
    int n;
    cin >> n;
    vector<int> nums(n);
    for (int i = 0; i < n; i++) {
        cin >> nums[i];
    }
    
    unordered_map<int, int> last_index;
    vector<int> dp(n, 1);
    vector<int> next_index(n, -1);
    int max_index = 0;
    
    for (int i = 0; i < n; i++) {
        int num = nums[i];
        if (last_index.count(num - 1)) {
            int index = last_index[num - 1];
            if (dp[i] < dp[index] + 1) {
                dp[i] = dp[index] + 1;
                next_index[i] = index;
            }   
        }
        last_index[num] = i;
        if (dp[max_index] < dp[i]) {
            max_index = i;
        }
    }
    
    set<int> selected_indices;
    int current_index = max_index;
    while (current_index >= 0) {
        selected_indices.insert(current_index + 1);
        current_index = next_index[current_index];
    }
    int num_selected_indices = selected_indices.size();
    cout << num_selected_indices << "\n";
    for (int num : selected_indices) {
        cout << num << " ";
    }
    cout << "\n";
}


int main() {
    long long t;
    // cin >> t;
    t=1;
    for (long long i = 1; i <= t; i++) {
        solve(i);
    }
    return 0;
}
