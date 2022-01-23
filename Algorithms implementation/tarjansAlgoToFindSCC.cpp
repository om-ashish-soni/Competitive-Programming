// { Driver Code Starts
#include<bits/stdc++.h>
using namespace std;

 // } Driver Code Ends
//User function template for C++

class Solution
{
	public:
    //Function to return a list of lists of integers denoting the members 
    //of strongly connected components in the given graph.
    void findScc(vector<vector<int>>& adj,vector<vector<int>>& scc,vector<bool>& recStack,vector<bool>& visited,vector<int> &disc,vector<int> &low,int &clocktime,stack<int>& stk,int i){
        int V=(int)adj.size();
        if(i>=V) return ;
        if(visited[i]) return;
        // cout<<"in "<<i<<endl;
        visited[i]=true;
        recStack[i]=true;
        clocktime++;
        disc[i]=low[i]=clocktime;
        stk.push(i);
        for(auto neb:adj[i]){
            if(!visited[neb]){ 
                findScc(adj,scc,recStack,visited,disc,low,clocktime,stk,neb);
                low[i]=min(low[i],low[neb]);
            }else{
                //attention ,!! please , here we are ignoring cross edge
                // and taking only back edge because taking cross edge will not generate scc
                // if it was so than this vertax would have already visited while visiting that neb , okkk !!!
                if(recStack[neb]) 
                low[i]=min(low[i],disc[neb]);
            }
        }
        // cout<<i<<" "<<disc[i]<<" "<<low[i]<<endl;
        if(disc[i] == low[i]){
            // cout<<"for  "<<i<<" disc and low are same "<<endl;
            int sz=scc.size();
            scc.push_back(*new vector<int>);
            vector<int>& component=scc[sz];
            while(i != stk.top()){
                component.push_back(stk.top());
                recStack[stk.top()]=false;
                stk.pop();
            }
            // cout<<"on top "<<stk.top()<<endl;
            component.push_back(stk.top());
            recStack[stk.top()]=false;
            stk.pop();
            
        }
    }
    vector<vector<int>> tarjans(int V, vector<int> adj[])
    {
        vector<vector<int>> adj1(V);
        for(int i=0;i<V;i++){
            for(auto neb:adj[i]){
                adj1[i].push_back(neb);
            }
        }
        vector<vector<int>> scc;
        vector<bool> recStack(V,false),visited(V,false);
        vector<int> disc(V,0),low(V,0);
        stack<int> stk;
        int clocktime=0;
        for(int i=0;i<V;i++) if(!visited[i]) findScc(adj1,scc,recStack,visited,disc,low,clocktime,stk,i);
        for(auto &component:scc){
            sort(component.begin(),component.end());
        }
        sort(scc.begin(),scc.end());
        return scc;
        //code here
    }
};

// { Driver Code Starts.


int main()
{
    
    int t;
    cin >> t;
    while(t--)
    {
        int V, E;
        cin >> V >> E;

        vector<int> adj[V];

        for(int i = 0; i < E; i++)
        {
            int u, v;
            cin >> u >> v;
            adj[u].push_back(v);
        }

        Solution obj;
        vector<vector<int>> ptr = obj.tarjans(V, adj);

        for(int i=0; i<ptr.size(); i++)
        {
            for(int j=0; j<ptr[i].size(); j++)
            {
                if(j==ptr[i].size()-1)
                    cout<<ptr[i][j];
                else
                    cout<<ptr[i][j]<<" ";
            }
            cout<<',';
        }
        cout<<endl;
    }

    return 0;
}

  // } Driver Code Ends
