class Solution {
public:
    int minimumTotal(vector<vector<int>>& triangle,vector<vector<int>> &v,int i=0,int j=0) {
        if(i==triangle.size()) return 0;
        if(j == triangle[i].size()) return INT_MAX;
        if(v[i][j] != INT_MAX) return v[i][j];
        v[i][j]=triangle[i][j];
        v[i][j]+=min(minimumTotal(triangle,v,i+1,j),minimumTotal(triangle,v,i+1,j+1));
        return v[i][j];
    }
    int minimumTotal(vector<vector<int>> &triangle){
        vector<int> temp(triangle[triangle.size()-1].size(),INT_MAX);
        vector<vector<int>> v(triangle.size(),temp);
        return minimumTotal(triangle,v);
    }
};