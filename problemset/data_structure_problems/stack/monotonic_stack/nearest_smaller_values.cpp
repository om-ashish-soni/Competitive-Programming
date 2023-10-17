// problem link : https://cses.fi/problemset/task/1645/
// solution : below code

#include <iostream>
#include <vector>
#include <stack>
using namespace std;

void solve(int testcase) {
    int n;
    cin >> n; // Using cin for input

    vector<int> heights(n);
    for (int i = 0; i < n; i++) {
        cin >> heights[i];
    }

    stack<pair<int, int>> descending_heights;
    vector<int> answer(n, 0);

    for (int i = 0; i < n; i++) {
        while (!descending_heights.empty() && descending_heights.top().first >= heights[i]) {
            descending_heights.pop();
        }

        if (!descending_heights.empty()) {
            answer[i] = descending_heights.top().second + 1;
        }

        descending_heights.push({heights[i], i});
    }

    for (int i = 0; i < n; i++) {
        cout << answer[i] << " ";
    }
    cout << endl;
}
