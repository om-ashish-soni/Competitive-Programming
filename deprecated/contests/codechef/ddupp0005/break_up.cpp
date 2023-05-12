// Problem link : https://www.codechef.com/ZCOPRAC/problems/ZCO15001
// Solution : below code

#include<bits/stdc++.h>
#define int long long
#define endl "\n"
using namespace std;
bool memo[310][310];
vector<int> arr;
bool isPal(int start,int end){
	if(start==end) return true;
	if((end-start<3) || memo[start+1][end-1]){
		bool res = (arr[start]==arr[end]);
		memo[start][end]=res;
		return res;
	}
	memo[start][end]=false;
	return false;
}
void solve(){
	int n;
	cin>>n;
	arr.resize(n);
	vector<int> v(n,LLONG_MAX);
	for(int i=0;i<n;i++) {cin>>arr[i];}
	v[0]=1;
	for(int i=1;i<n;i++){
		v[i]=min(v[i],v[i-1]+1);
		for(int j=i-1;j>=0;j--){
			int start(j),end(i);
			if(isPal(start,end)) v[i]=min(v[i],(start>0)?(1+v[start-1]):(1));
		}
	}
	cout<<v[n-1]<<endl;
}
signed main(){
	ios_base::sync_with_stdio(false);
    cin.tie(NULL);
	solve();
	return 0;
}
