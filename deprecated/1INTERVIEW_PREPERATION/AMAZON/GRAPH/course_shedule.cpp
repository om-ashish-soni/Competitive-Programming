// problem link : https://leetcode.com/problems/course-schedule/
// solution : below code

class Solution {
public:
    vector<bool> recstack,visited;
    bool iscycle(vector<vector<int>>& graph,int u){
        if(recstack[u]) return true;
        recstack[u]=true;
        visited[u]=true;
        for(auto node:graph[u]){
            if(visited[node]){
                if(recstack[node]) return true;
            }else{
                if(iscycle(graph,node)) return true;
            }
        }
        recstack[u]=false;
        return false;
    }
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        vector<vector<int>> graph(numCourses);
        for(auto &edge:prerequisites){
            graph[edge[0]].push_back(edge[1]);
        }
        recstack.assign(numCourses,false);
        visited.assign(numCourses,false);
        for(int i=0;i<numCourses;i++){
            if(visited[i]==false && iscycle(graph,i)) return false;
        }
        return true;
    }
};
