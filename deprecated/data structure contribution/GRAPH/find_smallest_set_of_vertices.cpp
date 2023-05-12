class Solution {
public:
    vector<int> findSmallestSetOfVertices(int n, vector<vector<int>>& edges) {
        vector<int> v1(n,1),v2;
        for(auto &v:edges){
            v1[v[1]]=0;
        }
        for(int i=0;i<n;i++){
            if(v1[i] == 1) v2.push_back(i);
        }
        return v2;
    }
};