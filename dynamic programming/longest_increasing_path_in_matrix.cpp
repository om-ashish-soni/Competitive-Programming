// problem link : https://leetcode.com/problems/longest-increasing-path-in-a-matrix/
// solution : below code

#define vi vector<int>
#define vvi vector<vector<int>>

class Solution {
public:
    inline bool check(int i,int j,int m,int n){
        return (i>=0 and j>=0 and i<m and j<n);
    }
    int longestIncreasingPath(vector<vector<int>>& matrix) {
        int m=matrix.size();
        int n=matrix.front().size();
        vvi idp(m,vi(n,1));
        vvi ddp(m,vi(n,1));
        
        for(int i=0;i<m;i++){
            for(int j=0;j<n;j++){
                if(check(i+1,j,m,n)){
                    if(matrix[i+1][j]<matrix[i][j]){
                        ddp[i+1][j]=max(ddp[i+1][j],1+ddp[i][j]);
                    }else if(matrix[i+1][j]>matrix[i][j]){
                        idp[i+1][j]=max(idp[i+1][j],1+idp[i][j]);
                    }
                }
                if(check(i-1,j,m,n)){
                    if(matrix[i-1][j]<matrix[i][j]){
                        ddp[i-1][j]=max(ddp[i-1][j],1+ddp[i][j]);
                    }else if(matrix[i-1][j]>matrix[i][j]){
                        idp[i-1][j]=max(idp[i-1][j],1+idp[i][j]);
                    }
                }
                if(check(i,j+1,m,n)){
                    if(matrix[i][j+1]<matrix[i][j]){
                        ddp[i][j+1]=max(ddp[i][j+1],1+ddp[i][j]);
                    }else if(matrix[i][j+1]>matrix[i][j]){
                        idp[i][j+1]=max(idp[i][j+1],1+idp[i][j]);
                    }
                }
                if(check(i,j-1,m,n)){
                    if(matrix[i][j-1]<matrix[i][j]){
                        ddp[i][j-1]=max(ddp[i][j-1],1+ddp[i][j]);
                    }else if(matrix[i][j-1]>matrix[i][j]){
                        idp[i][j-1]=max(idp[i][j-1],1+idp[i][j]);
                    }
                }
            }
            for(int j=n-1;j>=0;j--){
                if(check(i+1,j,m,n)){
                    if(matrix[i+1][j]<matrix[i][j]){
                        ddp[i+1][j]=max(ddp[i+1][j],1+ddp[i][j]);
                    }else if(matrix[i+1][j]>matrix[i][j]){
                        idp[i+1][j]=max(idp[i+1][j],1+idp[i][j]);
                    }
                }
                if(check(i-1,j,m,n)){
                    if(matrix[i-1][j]<matrix[i][j]){
                        ddp[i-1][j]=max(ddp[i-1][j],1+ddp[i][j]);
                    }else if(matrix[i-1][j]>matrix[i][j]){
                        idp[i-1][j]=max(idp[i-1][j],1+idp[i][j]);
                    }
                }
                if(check(i,j+1,m,n)){
                    if(matrix[i][j+1]<matrix[i][j]){
                        ddp[i][j+1]=max(ddp[i][j+1],1+ddp[i][j]);
                    }else if(matrix[i][j+1]>matrix[i][j]){
                        idp[i][j+1]=max(idp[i][j+1],1+idp[i][j]);
                    }
                }
                if(check(i,j-1,m,n)){
                    if(matrix[i][j-1]<matrix[i][j]){
                        ddp[i][j-1]=max(ddp[i][j-1],1+ddp[i][j]);
                    }else if(matrix[i][j-1]>matrix[i][j]){
                        idp[i][j-1]=max(idp[i][j-1],1+idp[i][j]);
                    }
                }
            }
        }
        for(int i=m-1;i>=0;i--){
            for(int j=0;j<n;j++){
                if(check(i+1,j,m,n)){
                    if(matrix[i+1][j]<matrix[i][j]){
                        ddp[i+1][j]=max(ddp[i+1][j],1+ddp[i][j]);
                    }else if(matrix[i+1][j]>matrix[i][j]){
                        idp[i+1][j]=max(idp[i+1][j],1+idp[i][j]);
                    }
                }
                if(check(i-1,j,m,n)){
                    if(matrix[i-1][j]<matrix[i][j]){
                        ddp[i-1][j]=max(ddp[i-1][j],1+ddp[i][j]);
                    }else if(matrix[i-1][j]>matrix[i][j]){
                        idp[i-1][j]=max(idp[i-1][j],1+idp[i][j]);
                    }
                }
                if(check(i,j+1,m,n)){
                    if(matrix[i][j+1]<matrix[i][j]){
                        ddp[i][j+1]=max(ddp[i][j+1],1+ddp[i][j]);
                    }else if(matrix[i][j+1]>matrix[i][j]){
                        idp[i][j+1]=max(idp[i][j+1],1+idp[i][j]);
                    }
                }
                if(check(i,j-1,m,n)){
                    if(matrix[i][j-1]<matrix[i][j]){
                        ddp[i][j-1]=max(ddp[i][j-1],1+ddp[i][j]);
                    }else if(matrix[i][j-1]>matrix[i][j]){
                        idp[i][j-1]=max(idp[i][j-1],1+idp[i][j]);
                    }
                }
            }
            for(int j=n-1;j>=0;j--){
                if(check(i+1,j,m,n)){
                    if(matrix[i+1][j]<matrix[i][j]){
                        ddp[i+1][j]=max(ddp[i+1][j],1+ddp[i][j]);
                    }else if(matrix[i+1][j]>matrix[i][j]){
                        idp[i+1][j]=max(idp[i+1][j],1+idp[i][j]);
                    }
                }
                if(check(i-1,j,m,n)){
                    if(matrix[i-1][j]<matrix[i][j]){
                        ddp[i-1][j]=max(ddp[i-1][j],1+ddp[i][j]);
                    }else if(matrix[i-1][j]>matrix[i][j]){
                        idp[i-1][j]=max(idp[i-1][j],1+idp[i][j]);
                    }
                }
                if(check(i,j+1,m,n)){
                    if(matrix[i][j+1]<matrix[i][j]){
                        ddp[i][j+1]=max(ddp[i][j+1],1+ddp[i][j]);
                    }else if(matrix[i][j+1]>matrix[i][j]){
                        idp[i][j+1]=max(idp[i][j+1],1+idp[i][j]);
                    }
                }
                if(check(i,j-1,m,n)){
                    if(matrix[i][j-1]<matrix[i][j]){
                        ddp[i][j-1]=max(ddp[i][j-1],1+ddp[i][j]);
                    }else if(matrix[i][j-1]>matrix[i][j]){
                        idp[i][j-1]=max(idp[i][j-1],1+idp[i][j]);
                    }
                }
            }
        }
        int mx=1;
        for(int i=0;i<m;i++){
            for(int j=0;j<n;j++){
                mx=max(mx,idp[i][j]+ddp[i][j]-1);
            }
        }
        return mx;
    }
    
};
