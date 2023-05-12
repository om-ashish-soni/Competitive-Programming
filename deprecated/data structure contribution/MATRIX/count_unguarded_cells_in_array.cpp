// problem link : https://leetcode.com/contest/biweekly-contest-77/problems/count-unguarded-cells-in-the-grid/
// solution : below code

class Solution {
public:
    int countUnguarded(int m, int n, vector<vector<int>>& guards, vector<vector<int>>& walls) {
        vector<vector<bool>> isg(m,*new vector<bool>(n,false));
        vector<vector<bool>> isw(m,*new vector<bool>(n,false));
        vector<vector<bool>> safe(m,*new vector<bool>(n,true));
        for(auto &row:guards){
            isg[row[0]][row[1]]=true;
        }
        for(auto &row:walls){
            isw[row[0]][row[1]]=true;
        }
        for(int i=0;i<m;i++){
            int myg=-1;
            int myw=-1;
            for(int j=0;j<n;j++){
                if(isg[i][j]){
                    myg=j;
                    safe[i][j]=false;
                }else if(isw[i][j]){
                    myw=j;
                    safe[i][j]=false;
                }else{
                    if(myg != -1 and (myw==-1 or myg>myw)){
                        safe[i][j]=false;
                    }
                }
            }
            myg=-1;
            myw=-1;
            for(int j=n-1;j>=0;j--){
                if(isg[i][j]){
                    myg=j;
                    safe[i][j]=false;
                }else if(isw[i][j]){
                    myw=j;
                    safe[i][j]=false;
                }else{
                    if(myg != -1 and (myw==-1 or myg<myw)){
                        safe[i][j]=false;
                    }
                }
            }
        }
        for(int j=0;j<n;j++){
            int myg=-1;
            int myw=-1;
            
            for(int i=0;i<m;i++){
                if(isg[i][j]){
                    myg=i;
                    safe[i][j]=false;
                }else if(isw[i][j]){
                    myw=i;
                    safe[i][j]=false;
                }else{
                    if(myg != -1 and (myw==-1 or myg>myw)){
                        safe[i][j]=false;
                    }
                }
            }
            myg=-1;
            myw=-1;
            for(int i=m-1;i>=0;i--){
                
                if(isg[i][j]){
                    myg=i;
                    safe[i][j]=false;
                }else if(isw[i][j]){
                    myw=i;
                    safe[i][j]=false;
                }else{
                    
                    if(myg != -1 and (myw==-1 or myg<myw)){
                        
                        safe[i][j]=false;
                    }
                }
                
            }
        }
        int safeplaces=0;
        for(int i=0;i<m;i++){
            for(int j=0;j<n;j++){
                if(safe[i][j]) safeplaces++;
            }
        }
        cout<<safeplaces<<endl;
        return safeplaces;
    }
};
