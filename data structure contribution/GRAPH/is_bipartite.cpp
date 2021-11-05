class Solution {
public:
    bool isBipartite(vector<vector<int>>& graph,vector<int>& color,int i=0){
        if(color[i]==-1){
            color[i]=0;
        }
        for(int j=0;j<graph[i].size();j++){
            if(color[graph[i][j]]==color[i]) throw false;
            if(color[graph[i][j]] == -1){
                color[graph[i][j]]=(color[i]+1)%2;
                isBipartite(graph,color,graph[i][j]);
            }
        }
        return true;
    }
    bool isBipartite(vector<vector<int>>& graph) {
        vector<int> color(graph.size(),-1);
        try{
            for(int i=0;i<graph.size();i++){
                if(-1 == color[i]){
                    isBipartite(graph,color,i);
                }
            }
        }catch(...){
            return false;
        }
        return true;
    }
};