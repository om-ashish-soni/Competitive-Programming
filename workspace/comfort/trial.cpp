#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void generateLists(vector<vector<int>>& result, vector<int>& currList, int n, int i) {
    // base case: if the current list is of length n, add it to the result
    if (i == n + 1) {
        result.push_back(currList);
        return;
    }

    // try all possible values of ai that satisfy the condition i - n + 1 <= ai <= i - 1
    for (int j = i - n + 1; j <= i - 1; j++) {
        // check if ai != -aj for all j < i
        if(j==0) continue;
        bool valid = true;
        for (int k = 1; k < i; k++) {
            if (currList[k] == -j) {
                valid = false;
                break;
            }
        }

        if (valid) {
            currList[i] = j; // set ai to j
            generateLists(result, currList, n, i+1); // recursively generate the next element of the list
        }
    }
}

int main() {
    int n;
    cin >> n;

    vector<vector<int>> result;
    vector<int> currList(n+1);

    generateLists(result, currList, n, 1);

    // print the result
    for (auto& list : result) {
        for (int i = 1; i <= n; i++) {
            cout << list[i] << " ";
        }
        cout << endl;
    }

    return 0;
}
