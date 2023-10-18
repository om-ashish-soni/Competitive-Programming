
long long maximum_subarray_sum_range(vector<long long>& v, int a, int b) {
    int n = v.size();

    vector<long long> prefixSum = v;
    for (int i = 1; i < n; ++i) {
        prefixSum[i] += prefixSum[i - 1];
    }

    long long maxSum = LLONG_MIN;
    priority_queue<pair<long long, int>> maxHeap;
    vector<bool> visited(n, false);

    for (int i = a - 1; i < b - 1; ++i) {
        maxHeap.push({prefixSum[i], i});
    }

    for (int i = 0; i < n; ++i) {
        if (i + a - 1 >= n) break;

        // Pushing
        if (i + b - 1 < n) maxHeap.push({prefixSum[i + b - 1], i + b - 1});

        // Getting max
        while (!maxHeap.empty() && visited[maxHeap.top().second]) {
            maxHeap.pop();
        }

        if (!maxHeap.empty()) {
            long long current = maxHeap.top().first - prefixSum[i] + v[i];
            maxSum = max(maxSum, current);
        }

        // Popping
        visited[i + a - 1] = true;
    }

    return maxSum;
}
