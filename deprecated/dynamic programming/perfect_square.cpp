// problem link : https://leetcode.com/problems/perfect-squares/
// solution : below code

vector<vector<int>> dp;
bool isinit=false;
void init(){
    dp=*new vector(110,*new vector<int>(10010,0));
    for(int j=1;j<10010;j++) dp[1][j]=j;
    for(int i=2;i<110;i++){
        for(int j=1;j<10010;j++){
            dp[i][j]=dp[i-1][j];
            if(j>=i*i){
                dp[i][j]=min(dp[i][j],1+dp[i][j-i*i]);
            }
        }
    }
    isinit=true;
}
class Solution {
public:
    
    
    
    int numSquares(int n) {
        if(isinit==false){
            init();    
            isinit=true;
        }
        cout<<dp[109][n]<<endl;
        return dp[109][n];
    }
    
};
