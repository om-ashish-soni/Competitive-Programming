// Problem link : https://practice.geeksforgeeks.org/problems/reach-the-target-1611827365/0/
// Solution : below code

#include<bits/stdc++.h>
#define int long long
#define endl "\n"
using namespace std;
void findPaths(int start,int dist,int end,int remainingSteps,vector<vector<int>>& paths,vector<int>& sol,int solIndex){
    // cout<<start<<","<<remainingSteps<<" ";
    if(remainingSteps==0){
        // cout<<start<<" "<<end<<endl;
        if(start==end){
            sol[solIndex]=start;
            paths.push_back(sol);
        }
        return;
    }
    sol[solIndex]=start;
    findPaths(start-dist,dist,end,remainingSteps-1,paths,sol,solIndex+1);
    findPaths(start+dist,dist,end,remainingSteps-1,paths,sol,solIndex+1);
}
void solve(){
	int a,b,c,d;
	cin>>a>>b>>c>>d;
	int start=a;
	int dist=b;
	int end=c;
	int remainingSteps=d;
	
	vector<vector<int>> paths;
	vector<int> sol(d+1,0);
	sol[0]=start;
	int solIndex=0;
	findPaths(start-dist,dist,end,remainingSteps-1,paths,sol,solIndex+1);
	findPaths(start+dist,dist,end,remainingSteps-1,paths,sol,solIndex+1);
	int no_of_paths=paths.size();
	for(auto &path:paths){
	    for(auto place:path) cout<<place<<" ";cout<<endl;
	}
	if(no_of_paths==0) cout<<-1<<endl;
}

signed main(){
	ios_base::sync_with_stdio(false);
    cin.tie(NULL);
//#ifndef ONLINE_JUDGE
//    freopen("input.txt", "r", stdin);
//    freopen("error.txt", "w", stderr);
//    freopen("output.txt", "w", stdout);
//#endif
	int t=1;
	cin>>t;
	while(t--){
		solve();
	}
	//cerr<<"time taken : "<<(float)clock()/CLOCKS_PER_SEC<<" secs"<<endl;
	return 0;
}
