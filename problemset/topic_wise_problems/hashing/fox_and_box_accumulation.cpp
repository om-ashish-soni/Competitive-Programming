// problem link : https://codeforces.com/contest/388/problem/A
// solution : below code

#include<bits/stdc++.h>
using namespace std;

using ll = long long;

void solve(int test_case) {
    int n;
    cin >> n;
    vector<int> nums(n);
    for (int i = 0; i < n; i++) {
        cin >> nums[i];
    }
    
    map<int, int> freq;
    for (int num : nums) {
        freq[num]++;
    }
    
    int num_buckets = 0;
    while (!freq.empty()) {
        num_buckets++;
        auto it = freq.begin();
        int bucket_size = 0;
        vector<int> to_remove;
        while (it != freq.end()) {
            int value = it->first;
            int value_freq = it->second;
            int num_to_take = min(value_freq, 1 + value - bucket_size);
            
            it->second -= num_to_take;
            bucket_size += num_to_take;
            if (it->second <= 0) {
                to_remove.push_back(value);
            }
            it = freq.upper_bound(value);
        }
        for (int num : to_remove) {
            freq.erase(num);
        }
    }
    
    cout << num_buckets << "\n";
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
