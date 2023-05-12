// problem link : https://leetcode.com/problems/find-winner-on-a-tic-tac-toe-game/description/
// solution : below code

class Solution {
public:
    vector<vector<int>> mat;
    bool detect(){
        // for(int i=0;i<3;i++){
        //     for(int j=0;j<3;j++){
        //         cout<<mat[i][j]<<" ";
        //     }
        //     cout<<endl;
        // }
        for(int i=0;i<3;i++){
            if(mat[i][0]==mat[i][1] && mat[i][1]==mat[i][2]) return true;
            if(mat[0][i]==mat[1][i] && mat[1][i]==mat[2][i]) return true;
        }
        bool cross1 = (mat[0][0]==mat[1][1] && mat[1][1]==mat[2][2]);
        bool cross2 = (mat[0][2]==mat[1][1] && mat[1][1]==mat[2][0]);
        return cross1 || cross2;
    }
    string tictactoe(vector<vector<int>>& moves) {
        mat.assign(3,vector<int>(3));
        for(int i=0;i<3;i++){
            for(int j=0;j<3;j++){
                mat[i][j]=1e5+i*3+j;
            }
        }
        int player=1;
        for(auto & pos:moves){
            int row=pos[0];
            int col=pos[1];
            mat[row][col]=player;
            bool b=detect();
            if(b){
                if(player==1) return "A";
                else return "B";
            }
            player^=1;
        }
        for(int i=0;i<3;i++){
            for(int j=0;j<3;j++){
                if(mat[i][j]>=1e5) return "Pending";
            }
        }return "Draw";
    }
};