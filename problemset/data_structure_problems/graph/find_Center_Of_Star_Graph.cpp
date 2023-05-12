class Solution {
public:
    int findCenter(vector<vector<int>>& edges) {
        vector<int> center(edges.size()+2,0);
        for(auto &v:edges){ center[v[0]]++,center[v[1]]++; }
        for(int i=1;i<=edges.size()+1;i++) if(center[i]==edges.size()) return i;
        return 0;
    }
};