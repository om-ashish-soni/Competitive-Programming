// Problem link : https://practice.geeksforgeeks.org/problems/longest-subarray-with-atmost-k-even-elements/0/
// Problem type : sliding window

#include<bits/stdc++.h>
#define int long long
#define endl "\n"
using namespace std;
void solve(){
	int n,k;
	cin>>n>>k;
	int arr[n];
	int l=0,r=0,evens=0,slidingWindow=0;
	for(int i=0;i<n;i++) cin>>arr[i];
	queue<int> evenIndices;
	while(l<=r && r<n){
	    if(!(arr[r]&1)){ 
	        evens++;
	        evenIndices.push(r);
	    }
	    if(evens>k){
	        l= 1 + evenIndices.front();
	        evenIndices.pop();
	        evens--;
	    }
        r++;
	    slidingWindow=max(slidingWindow,r-l);
	}
	cout<<slidingWindow<<endl;
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
