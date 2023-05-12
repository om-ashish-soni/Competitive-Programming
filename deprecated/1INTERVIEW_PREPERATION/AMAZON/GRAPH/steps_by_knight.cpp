// problem link : https://practice.geeksforgeeks.org/problems/steps-by-knight5927/1/
// solution : below code

// { Driver Code Starts
#include<bits/stdc++.h>
using namespace std;

 // } Driver Code Ends
class Solution 
{
    public:
    //Function to find out minimum steps Knight needs to reach target position.
    inline bool check(int i,int j,int n){
        return (i>0 && j>0 && i<n && j<n);
    }
    void relax(vector<vector<long long>> & dp,int i,int j,int n){
        if(dp[i][j] == INT_MAX) return;
        int fi,fj,ci,cj;
        fi=i-1;fj=j-2;
        
        if(check(fi,fj,n)){
            dp[fi][fj]=min(dp[fi][fj],1+dp[i][j]);
            // if(check())
        }
        
        fi=i-1;fj=j+2;
        if(check(fi,fj,n)){
            dp[fi][fj]=min(dp[fi][fj],1+dp[i][j]);
        }
        
        fi=i-2;fj=j-1;
        if(check(fi,fj,n)){
            dp[fi][fj]=min(dp[fi][fj],1+dp[i][j]);
        }
        
        fi=i-2;fj=j+1;
        if(check(fi,fj,n)){
            dp[fi][fj]=min(dp[fi][fj],1+dp[i][j]);
        }
        
        fi=i+1;fj=j-2;
        if(check(fi,fj,n)){
            dp[fi][fj]=min(dp[fi][fj],1+dp[i][j]);
        }
        
        fi=i+1;fj=j+2;
        if(check(fi,fj,n)){
            dp[fi][fj]=min(dp[fi][fj],1+dp[i][j]);
        }
        
        fi=i+2;fj=j-1;
        if(check(fi,fj,n)){
            dp[fi][fj]=min(dp[fi][fj],1+dp[i][j]);
        }
        
        fi=i+2;fj=j+1;
        if(check(fi,fj,n)){
            dp[fi][fj]=min(dp[fi][fj],1+dp[i][j]);
        }
        
    }
    void reduce(vector<vector<long long>> & dp,int fi,int fj,int i,int j,int n){
        if(check(fi,fj,n)){
            if(dp[fi][fj]>1+dp[i][j]){
                dp[fi][fj]=1+dp[i][j];
                relax(dp,fi,fj,n);
            }
        }
    }
    void spread(vector<vector<long long>> & dp,int i,int j,int n){
        if(dp[i][j] == INT_MAX) return;
        int fi,fj;
        fi=i-1;fj=j-2;reduce(dp,fi,fj,i,j,n);
        fi=i-1;fj=j+2;reduce(dp,fi,fj,i,j,n);
        fi=i-2;fj=j-1;reduce(dp,fi,fj,i,j,n);
        fi=i-2;fj=j+1;reduce(dp,fi,fj,i,j,n);
        fi=i+1;fj=j-2;reduce(dp,fi,fj,i,j,n);
        fi=i+1;fj=j+2;reduce(dp,fi,fj,i,j,n);
        fi=i+2;fj=j-1;reduce(dp,fi,fj,i,j,n);
        fi=i+2;fj=j+1;reduce(dp,fi,fj,i,j,n);
        
    }
	int minStepToReachTarget(vector<int>&KnightPos,vector<int>&TargetPos,int N)
	{
	    int n=N+1;
	    vector<vector<long long>> dp(n,vector<long long>(n,INT_MAX));
	    int px=TargetPos[0],py=TargetPos[1];
	    int kx=KnightPos[0],ky=KnightPos[1];
	    if(n==1 || (px==kx && py==ky)) return 0;
	    if(n==2) return -1;
	    if(n==3 && ((px==2 && py==2) || (kx==2 && ky==2))) return -1;
	    
	    dp[kx][ky]=0;
	    
	    for(int i=1;i<n;i++){
	        for(int j=1;j<n;j++){
	            spread(dp,i,j,n);
	        }
	        for(int j=n-1;j>0;j--){
	            spread(dp,i,j,n);
	        }
	    }
	    for(int i=n-1;i>0;i--){
	        for(int j=1;j<n;j++){
	            spread(dp,i,j,n);
	        }
	        for(int j=n-1;j>0;j--){
	            spread(dp,i,j,n);
	        }
	    }
	    if(dp[px][py]==INT_MAX) return -1;
	    return dp[px][py];
	}
};

// { Driver Code Starts.
int main(){
	int tc;
	cin >> tc;
	while(tc--){
		vector<int>KnightPos(2);
		vector<int>TargetPos(2);
		int N;
		cin >> N;
		cin >> KnightPos[0] >> KnightPos[1];
		cin >> TargetPos[0] >> TargetPos[1];
		Solution obj;
		int ans = obj.minStepToReachTarget(KnightPos, TargetPos, N);
		cout << ans <<"\n";
	}
	return 0;
}  // } Driver Code Ends
