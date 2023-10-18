// problem link : https://cses.fi/problemset/task/1077/
// solution : below code

#include<bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define int long long

class BalancedHeap {
private:
    map<int, int> elementIndexMap;
    priority_queue<pair<int,int>> maxHeap;
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> minHeap;
    int maxSize = 0;
    int minSize = 0;
    int minSum=0,maxSum=0;

    bool LOG_DEBUG=false;
    

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

    void pushMinHeap(pair<int,int> top){
        minSum+=top.first;
        minHeap.push(top);
        minSize++;
        elementIndexMap[top.second] = 0;
    }
    void pushMaxHeap(pair<int,int> top){
        maxSum+=top.first;
        maxHeap.push(top);
        maxSize++;
        elementIndexMap[top.second] = 1;
    }
    bool popMaxHeap(){
        if(maxHeap.empty()) return false;
        int value=maxHeap.top().first;
        int index=maxHeap.top().second;
        maxHeap.pop();
        if (elementIndexMap.count(index) && elementIndexMap[index]==1) {
            maxSum-=value;
            maxSize--;
            return true;
        }
        return false;
    }
    bool popMinHeap(){
        if(minHeap.empty()) return false;
        int value=minHeap.top().first;
        int index=minHeap.top().second;
        minHeap.pop();
        if (elementIndexMap.count(index) && elementIndexMap[index]==0) {
            minSum-=value;
            minSize--;
            return true;
        }
        return false;
    }

    void balance() {
        clean();
        if (LOG_DEBUG) cout << "before balance: " << minSize << " vs " << maxSize << endl;
        while (!maxHeap.empty() && minSize + 1 <= maxSize - 1) {
            pair<int, int> top = maxHeap.top();
            int index = top.second;

            if (popMaxHeap()) {
                pushMinHeap(top);
                if (LOG_DEBUG) cout << index << " on " << 0 << endl;
            }
        }

        if (LOG_DEBUG) cout << "done first: " << minSize << " vs " << maxSize << endl;

        while (!minHeap.empty() && minSize > maxSize) {
            pair<int, int> top = minHeap.top();
            int index = top.second;

            if (popMinHeap()) {
                pushMaxHeap(top);
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
            pushMaxHeap({elem, index});
        } else {
            pushMinHeap({elem, index});
        }
        balance();
        if (LOG_DEBUG) cout << index << " inserted " << elementIndexMap[index] << endl;
    }

    void remove(int value,int index) {
        int indexOfHeap = elementIndexMap[index];
        if (indexOfHeap == 0) {
            minSum-=value;
            minSize--;
        } else if (indexOfHeap == 1) {
            maxSum-=value;
            maxSize--;
        }
        elementIndexMap.erase(index);
        balance();
        if (LOG_DEBUG) cout << index << " removed" << endl;
    }

    int getMedian() {
        balance();
        if (maxHeap.empty()) {
            cout << "EMPTY HEAP OCCUR" << endl;
            throw "EMPTY HEAP OCCUR";
        }
        return maxHeap.top().first;
    }

    int getCost(){
        
        int median=getMedian();
        int minHeapCost=(maxSize*median)-maxSum;
        int maxHeapCost=minSum-(minSize*median);    
        // cout<<minHeapCost<<" vs "<<maxHeapCost<<endl;
        return minHeapCost+maxHeapCost;
    }

    
};

void solve(int testcase) {
    int n, k;
    cin >> n >> k;
    vector<int> v(n);

    for (int i = 0; i < n; i++) {
        cin >> v[i];
    }

    BalancedHeap bh;

    for (int i = 0; i < k - 1; i++) {
        bh.insert(v[i], i);
    }

    for (int i = k - 1; i < n; i++) {
        bh.insert(v[i], i);
        cout << bh.getCost() << " ";
        bh.remove(v[i - k + 1], i - k + 1);
    }
}

signed main() {

    solve(0);

    return 0;
}



