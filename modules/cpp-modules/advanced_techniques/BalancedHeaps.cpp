#include<bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define int long long

#define LOG_DEBUG false
using pii = pair<int, int>;
using vpii = vector<pii>;

class BalancedHeap {
public:
    
private:
    map<int, int> elementIndexMap;
    priority_queue<pii> maxHeap;
    priority_queue<pii, vpii, greater<pii>> minHeap;
    int maxSize = 0;
    int minSize = 0;
    

    void clean() {
        while (!maxHeap.empty()) {
            int index = maxHeap.top().second;
            if (elementIndexMap.count(index) == 0) {
                maxHeap.pop();
            } else {
                break;
            }
        }
        while (!minHeap.empty()) {
            int index = minHeap.top().second;
            if (elementIndexMap.count(index) == 0) {
                minHeap.pop();
            } else {
                break;
            }
        }
    }

    void balance() {
        clean();
        if (LOG_DEBUG) cout << "before balance: " << minSize << " vs " << maxSize << endl;
        while (!maxHeap.empty() && minSize + 1 <= maxSize - 1) {
            pair<int, int> top = maxHeap.top();
            maxHeap.pop();
            int index = top.second;
            if (elementIndexMap.count(index)) {
                maxSize--;
                minHeap.push(top);
                minSize++;
                elementIndexMap[index] = 0;
                if (LOG_DEBUG) cout << index << " on " << 0 << endl;
            }
        }
        if (LOG_DEBUG) cout << "done first: " << minSize << " vs " << maxSize << endl;
        while (!minHeap.empty() && minSize > maxSize) {
            pair<int, int> top = minHeap.top();
            minHeap.pop();
            int index = top.second;
            if (elementIndexMap.count(index)) {
                minSize--;
                maxHeap.push(top);
                maxSize++;
                elementIndexMap[index] = 1;
                if (LOG_DEBUG) cout << index << " on " << 1 << endl;
            }
        }
        if (LOG_DEBUG) cout << "after balance: " << minSize << " vs " << maxSize << endl;
    }

public:

    BalancedHeap() {
        // Constructor, if needed
    }

    void insert(int elem, int index) {
        clean();
        if (minHeap.empty() || elem < minHeap.top().first) {
            maxHeap.push({elem, index});
            maxSize++;
            elementIndexMap[index] = 1;
        } else {
            minHeap.push({elem, index});
            minSize++;
            elementIndexMap[index] = 0;
        }
        balance();
        if (LOG_DEBUG) cout << index << " inserted " << elementIndexMap[index] << endl;
    }

    void remove(int index) {
        int indexOfHeap = elementIndexMap[index];
        if (indexOfHeap == 0) {
            minSize--;
        } else if (indexOfHeap == 1) {
            maxSize--;
        }
        elementIndexMap.erase(index);
        balance();
        if (LOG_DEBUG) cout << index << " removed" << endl;
    }

    int get() {
        balance();
        if (maxHeap.empty()) {
            cout << "EMPTY HEAP OCCUR" << endl;
            throw "EMPTY HEAP OCCUR";
        }
        return maxHeap.top().first;
    }

    
};