// Problem link : https://leetcode.com/problems/max-increase-to-keep-city-skyline/
// Problem type : Greedy
class Solution {
public:
    int maxIncreaseKeepingSkyline(vector<vector<int>>& grid) {
        int n=grid.size();
        vector<int> rowMax(n,0);
        vector<int> colMax(n,0);
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                int currBuilding=grid[i][j];
                rowMax[i]=max(rowMax[i],currBuilding);
                colMax[j]=max(colMax[j],currBuilding);
            }
        }
        int sum=0;
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                // cout<<"{ "<<rowMax[i] <<","<<colMax[j]<<" }"<<" _ ";
                sum+=min(rowMax[i],colMax[j])-grid[i][j];
            }
            // cout<<endl;
        }
        return sum;
    }
};
