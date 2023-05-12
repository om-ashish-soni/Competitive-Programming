class Solution {
public:
    bool detectionOfCycle(vector<vector<int>> &prereq,vector<bool> &visited,vector<bool> &recstack,int start){
        if(visited[start]==false){
            visited[start]=true;
            recstack[start]=true;
            for(int i=0;i<prereq[start].size();i++){
                if(!visited[i] && detectionOfCycle(prereq,visited,recstack,prereq[start][i])){
                    throw true;
                }else if(recstack[prereq[start][i]]){
                    throw true;
                }
            }
            recstack[start]=false;            
        }
        return false;
    }
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        vector<vector<int>> prereq(numCourses);
        for(auto &v:prerequisites){
            prereq[v[0]].push_back(v[1]);
        }
        for(int i=0;i<numCourses;i++){
            vector<bool> recstack(numCourses,0),visited(numCourses,0);
            try{bool res=detectionOfCycle(prereq,visited,recstack,i);}
            catch(...){ return false;}
        }
        return true;
    }
};