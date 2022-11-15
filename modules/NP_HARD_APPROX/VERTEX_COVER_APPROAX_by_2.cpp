#include <bits/stdc++.h>
 
using namespace std;
 
void vertexCover(vector<pair<int, int>> &edges, int n)
{
    vector<vector<int>> graph(n);
    for (auto &pr : edges)
    {
        int x = pr.first;
        int y = pr.second;
        graph[x].push_back(y);
        graph[y].push_back(x);
    }
    // for(int i=0;i<n;i++){
    //     cout<<i<<" : "<<endl;
    //     for(auto node:graph[i]) cout<<" -> "<<node<<" ";
    //     cout<<endl;
    // }
    map<pair<int, int>, bool> visited;
    vector<bool> solution(n, false);
 
    while (edges.size() > 0)
    {
        int sz = edges.size();
        int index = rand() % sz;
        pair<int, int> edge = edges[index];
        swap(edges[index], edges[sz - 1]);
        edges.pop_back();
        int x = edge.first;
        int y = edge.second;
        if (visited.count({x, y}) == 0 && visited.count({y, x}) == 0)
        {
            // cout<<"taking : "<<x<<" , "<<y<<endl;
            solution[x] = true;
            solution[y] = true;
            for (auto &node : graph[x])
            {
                visited[{x, node}] = true;
                // cout<<"marking : "<<node<<endl;
            }
            for (auto &node : graph[y])
            {
                visited[{y, node}] = true;
                // cout<<"marking : "<<node<<endl;
            }
            visited[{x, y}] = true;
        }
    }
    vector<int> cover;
    for (int i = 0; i < n; i++)
    {
        if (solution[i] == true)
        {
            cout << i << " ";
        }
        cover.push_back(i);
    }
    cout << endl;
    return;
}
int main()
{
    srand(time(0));
    vector<pair<int, int>> edges = {{0, 1}, {1, 2}, {2, 3}, {2, 4}, {3, 5}, {4, 5}, {4, 6}};
    int n = 7;
    vertexCover(edges, n);
    return 0;
}

