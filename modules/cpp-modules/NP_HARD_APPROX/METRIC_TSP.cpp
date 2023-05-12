#include <bits/stdc++.h>
using namespace std;
 
class disjointSet
{
    vector<int> ump;
 
public:
    vector<int> &getUmp()
    {
        return ump;
    }
    disjointSet(int n)
    {
        ump.assign(n + 1, -1);
    }
    int findSet(int u)
    {
        int r = u;
        while (ump[r] >= 0)
        {
            r = ump[r];
        }
        while (u != r)
        {
            int par = ump[u];
            ump[u] = r;
            u = par;
        }
        return r;
    }
    bool setUnion(int u, int v)
    {
        // cout<<"in setUnion "<<u<<" "<<v<<endl;
        int uroot = findSet(u);
        int vroot = findSet(v);
        // cout<<"root : "<<uroot<<" "<<vroot<<endl;
        if (uroot == vroot)
            return false;
        int uchild = ump[uroot];
        int vchild = ump[vroot];
        int totalChild = uchild + vchild;
 
        if (uchild > vchild)
        {
            ump[uroot] = vroot;
            ump[vroot] = totalChild;
        }
        else
        {
            ump[vroot] = uroot;
            ump[uroot] = totalChild;
        }
        return true;
    }
};
 
void kruskal(int n, vector<pair<int, pair<int, int>>> &edges, vector<pair<int, int>> &mst)
{
    disjointSet *ds = new disjointSet(n + 1);
    //kruskal starts here
    sort(edges.begin(), edges.end());
    for (auto &pr : edges)
    {
        int x = pr.second.first;
        int y = pr.second.second;
        bool shouldTake = ds->setUnion(x, y);
        if (shouldTake)
        {
            mst.push_back({x, y});
        }
    }
    //kruskal ends here
    delete ds;
    return;
}
void preorder(vector<vector<int>> &graph, vector<int> &sequence, int start, int par = -1)
{
    
    // cout<<"in preorder : "<<start<<endl;
    sequence.push_back(start);
    for (auto &child : graph[start])
    {
        if (child != par)
        {
            preorder(graph, sequence, child, start);
        }
    }
    return;
}
void TSP(vector<vector<int>> &graph, int start)
{
    int n = graph.size();
    vector<pair<int, pair<int, int>>> edges;
    vector<pair<int, int>> mst_edges;
    vector<vector<int>> mst_graph(n);
    vector<int> sequence;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (i != j)
            {
                edges.push_back({graph[i][j], {i, j}});
            }
        }
    }
 
    kruskal(n, edges, mst_edges);
 
    for (auto &edge : mst_edges)
    {
        int x = edge.first;
        int y = edge.second;
        mst_graph[x].push_back(y);
        mst_graph[y].push_back(x);
        // cout<<edge.first<<" , "<<edge.second<<" : cost = "<<graph[edge.first][edge.second]<<endl;
    }
 
    preorder(mst_graph, sequence, start);
    sequence.push_back(start);
    int sz = sequence.size();
    int total_cost = 0;
    cout << "sequence : ";
    for (int i = 0; i < sz; i++)
    {
        cout << sequence[i] + 1 << " ";
        if (i > 0)
        {
            int curr = sequence[i];
            int last = sequence[i - 1];
            total_cost += graph[last][curr];
        }
    }
    cout << endl;
    cout << "cost : " << total_cost << endl;
}
int main()
{
    vector<vector<int>> graph = {
        //     { 0, 10, 15, 20 },
        //   { 10, 0, 35, 25 },
        //   { 15, 35, 0, 30 },
        //   { 20, 25, 30, 0 }
        {0, 3, 4, 5, 6},
        {3, 0, 5, 3, 4},
        {4, 5, 0, 4, 4},
        {5, 3, 4, 0, 5},
        {6, 4, 4, 5, 0}};
    TSP(graph, 0);
    return 0;
}

