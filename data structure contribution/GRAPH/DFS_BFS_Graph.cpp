#include <map>
#include <set>
#include <list>
#include <cmath>
#include <ctime>
#include <deque>
#include <queue>
#include <stack>
#include <string>
#include <bitset>
#include <cstdio>
#include <limits>
#include <vector>
#include <climits>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <numeric>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <unordered_map>

using namespace std;
class Graph{
    map<int,vector<int>> adj;
    int len;
    map<int,bool> visited;
    public:
    Graph(int len){
        this->len=len;
    }
    void addEdge(int first,int second){
        adj[first].push_back(second);
        adj[second].push_back(first);
        visited[first]=false;
        visited[second]=false;
    }
    void BFS(int start){
        queue<int> q;
        q.push(start);
        while(!q.empty()){
            int current=q.front();
            if(!visited[current]){
                cout<<current<<" ";
                visited[current]=true;
            }
            q.pop();
            for(auto it=adj[current].begin();it!=adj[current].end();++it){
                if(!visited[*it]){ 
                    q.push(*it);
                    
                }
                
            }
        }
        
    }
    void DFS(int start){
        
        if(!visited[start]) cout<<start<<" ";
        visited[start]=true;
        for(auto it=adj[start].begin();it!=adj[start].end();++it){
            if(!visited[*it]){
                DFS(*it);
            }
        }
    }
    void refresh(){
        for(auto it=visited.begin();it!=visited.end();++it){
            visited[it->first]=false;
        }
    }
};
int main() {
    int n;
    cin>>n;
    int m;
    cin>>m;
    Graph g(n);
    for(int i=0;i<m;i++){
        int first,second;
        cin>>first>>second;
        g.addEdge( first,  second);
    }
    int start;
    cin>>start;
    // g.refresh();
    g.BFS(start);
    cout<<endl;
    g.refresh();
    g.DFS(start);
    cout<<endl;
    g.refresh();
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    return 0;
}