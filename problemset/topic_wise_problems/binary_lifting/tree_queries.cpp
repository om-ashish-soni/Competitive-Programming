// problem link : https://www.hackerearth.com/challenges/competitive/dsa-coding-contest-october-23/algorithm/tree-operations-2-e868a045/

// explaination : 

/*
* This solution is designed to solve a problem related to binary lifting and range queries on a tree. Here's a brief explanation of how it works:

The problem involves a tree with nodes, where each node has an associated value. The goal is to perform certain operations on paths within the tree.

The solution uses a data structure that stores binary lifting information, including the parent of each node at different levels, OR and XOR results for each node, and the depth of each node in the tree.

The dfs function is a depth-first search that computes the depth, parent nodes, OR results, and XOR results for each node in the tree. It initializes these values starting from the root node and working down to the leaf nodes.

The findLCA function (Lowest Common Ancestor) calculates the lowest common ancestor of two given nodes u and v in the tree. This is a crucial operation for many tree-related problems.

The findOR and findXOR functions compute the OR and XOR results along a path from node u to node v. These functions use the binary lifting information to efficiently compute the results.

In the main function, the code reads the number of nodes in the tree and the number of queries. It then reads the tree structure and node values.

For each query, it calculates the lowest common ancestor (LCA) of the given nodes u and v. Then, it computes OR and XOR results for the paths from both u and v to the LCA. Finally, it combines these results according to the specified formula and prints the result.

Overall, this solution efficiently handles tree-related queries by using binary lifting techniques and precomputing necessary information, making it a powerful tool for solving problems involving trees and path operations.





*/

// solution : below code

#include <iostream>
#include <vector>
using namespace std;

const long long MAXN = 200000 + 100; // Adjust this according to your needs
const int LOGN = 20; // Number of levels in the binary lifting

vector<int> treev[MAXN];
long long parent[MAXN][LOGN];
long long orResult[MAXN][LOGN];  // Stores the OR results for each node at different levels
long long xorResult[MAXN][LOGN]; // Stores the XOR results for each node at different levels
int depth[MAXN];
long long value[MAXN];

void dfs(int node, int par) {
    depth[node] = depth[par] + 1;
    parent[node][0] = par;
    orResult[node][0] = value[node];  // Initialize with its own value
    xorResult[node][0] = value[node]; // Initialize with its own value

    for (int i = 1; i < LOGN; i++) {
        parent[node][i] = parent[parent[node][i - 1]][i - 1];
        orResult[node][i] = orResult[node][i - 1] | orResult[parent[node][i - 1]][i - 1];
        xorResult[node][i] = xorResult[node][i - 1] ^ xorResult[parent[node][i - 1]][i - 1];
    }

    for (int child : treev[node]) {
        if (child != par) {
            dfs(child, node);
        }
    }
}

int findLCA(int u, int v) {
    if (depth[u] < depth[v]) {
        swap(u, v);
    }

    for (int i = LOGN - 1; i >= 0; i--) {
        if (depth[u] - (1 << i) >= depth[v]) {
            u = parent[u][i];
        }
    }

    if (u == v) return u;

    for (int i = LOGN - 1; i >= 0; i--) {
        if (parent[u][i] != parent[v][i]) {
            u = parent[u][i];
            v = parent[v][i];
        }
    }

    return parent[u][0];
}

long long findOR(int u, int v) {
    if (depth[u] < depth[v]) {
        swap(u, v);
    }
    long long ans = 0;
    for (int i = LOGN - 1; i >= 0; i--) {
        if (depth[u] - (1 << i) >= depth[v]) {
            ans |= orResult[u][i];
            u = parent[u][i];
        }
    }
    return ans;
}

long long findXOR(int u, int v) {
    if (depth[u] < depth[v]) {
        swap(u, v);
    }
    long long ans = 0;
    for (int i = LOGN - 1; i >= 0; i--) {
        if (depth[u] - (1 << i) >= depth[v]) {
            ans ^= xorResult[u][i];
            u = parent[u][i];
        }
    }
    return ans;
}

int main() {
    int n; // Number of nodes in the treev
    cin >> n;

    int q;
    cin >> q;
    for (int i = 0; i < MAXN; i++) {
        treev[i].clear();
    }

    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--;
        v--;
        treev[u].push_back(v);
        treev[v].push_back(u);
    }

    for (int i = 0; i < n; i++) {
        cin >> value[i];
    }

    depth[0] = -1; // Depth of the root node
    dfs(0, 0);

    for (int i = 0; i < q; i++) {
        int u, v;
        cin >> u >> v;
        u--;
        v--;

        int anc = findLCA(u, v);
        long long f1 = findOR(u, anc);
        long long f2 = findXOR(u, anc);
        long long s1 = findOR(v, anc);
        long long s2 = findXOR(v, anc);
        long long ctr = (f1 | s1 | value[anc]) + (f2 ^ s2 ^ value[anc]);
        cout << ctr << endl;
    }
    return 0;
}
