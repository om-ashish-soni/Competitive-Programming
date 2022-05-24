// problem link : https://leetcode.com/problems/set-matrix-zeroes/
// solution : below code

class Solution {
public:
    inline bool check(int i,int j,int n,int m){
        return i>=0 && j>=0 && i<n && j<n;
    }
    void setZeroes(vector<vector<int>>& matrix) {
        int n=matrix.size();
        int m=matrix.back().size();
        int not_present=-1;
        int MAX=4e4 + 2;
        vector<bool> v(MAX,false);
        for(auto &row:matrix){
            for(auto &elem:row){
                if(elem>=0 && elem<MAX) v[elem]=true;
            }
        }
        for(int i=0;i<MAX;i++){
            if(v[i]==false){
                not_present=i;
                break;
            }
        }
        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++){
                if(matrix[i][j]==0){
                    for(int ki=0;ki<n;ki++){
                        if(matrix[ki][j] != 0) matrix[ki][j]=not_present;
                    }
                    for(int kj=0;kj<m;kj++){
                        if(matrix[i][kj] != 0) matrix[i][kj]=not_present;
                    }
                }else{
                    if(check(i-1,j,n,m) && matrix[i-1][j]==0){
                        matrix[i][j]=not_present;
                    }
                    if(check(i,j-1,n,m) && matrix[i][j-1]==0){
                        matrix[i][j]=not_present;
                    }
                }
            }
        }
        for(auto &row:matrix){
            for(auto &elem:row){
                if(elem==not_present) elem=0;
            }
        }
        
    }
};
