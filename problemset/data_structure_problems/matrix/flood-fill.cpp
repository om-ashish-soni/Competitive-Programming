// problem link : https://leetcode.com/problems/flood-fill/description/
// solution : below code

class Solution {
public:
    vector<vector<int>> floodFill(vector<vector<int>>& image, int sr, int sc, int color) {
        int n=image.size();
        int m=image.front().size();
        vector<vector<bool>> marked(n,vector<bool>(m,false));
        queue<pair<int,int>> q;
        q.push({sr,sc});
        marked[sr][sc]=true;
        vector<vector<int>> v=image;
        while(q.size()>0){
            pair<int,int> top=q.front();
            q.pop();
            int x=top.first;
            int y=top.second;
            v[x][y]=color;
            for(int i=-1;i<=1;i++){
                for(int j=-1;j<=1;j++){
                    if(abs(i)==abs(j)) continue;
                    int u=x+i;
                    int v=y+j;
                    if(u>=0 && v>=0 && u<n && v<m && image[u][v] == image[x][y] && marked[u][v]==false){
                        marked[u][v]=true;
                        q.push({u,v});
                    }
                }
            }
        }
        return v;
    }
};