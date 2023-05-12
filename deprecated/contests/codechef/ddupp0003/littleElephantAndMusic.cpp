#include<bits/stdc++.h>
#define int long long
#define endl "\n"
using namespace std;
unordered_map<int,int> hashmp;
int n,b,l,sum,rem,ans,indx,*arr;
void solve(){
	sum=rem=ans=indx=0;
	hashmp.clear();
	scanf("%lld",&n);
	for(int i=0;i<n;i++){
		scanf("%lld %lld",&b,&l);
		if(hashmp[b]) hashmp[b]=min(hashmp[b],l);
		else hashmp[b]=l;
		sum+=l;
	}
	arr=(int*)malloc(hashmp.size()*sizeof(int));
	for(auto &pr:hashmp) rem+=arr[indx++]=pr.second;
	sort(arr,arr+indx);
	for(int i=0;i<indx;i++) ans+=((i+1)*arr[i]);
	free(arr);
	sum-=rem;
	ans+=(sum*indx);
	cout<<ans<<endl;
}

signed main(){
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("error.txt", "w", stderr);
    freopen("output.txt", "w", stdout);
#endif
	int t=1;
	scanf("%lld",&t);
	while(t--) solve();
	cerr<<"time taken : "<<(float)clock()/CLOCKS_PER_SEC<<" secs"<<endl;
	return 0;
}
