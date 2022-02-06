// Problem link : https://practice.geeksforgeeks.org/problems/geek-onacci-number-1611829559/0/
// Solution : below code

#include<bits/stdc++.h>
#define int long long
#define endl "\n"
using namespace std;
const int N=1e4+10;
const int mod=1e9+7;
int nfib[N];
void nFibonacci(){
    memset(nfib,0,sizeof(nfib));
	int n;
	cin>>nfib[0]>>nfib[1]>>nfib[2]>>n;
    for(int i=3;i<n;i++){
        nfib[i]=nfib[i-1]+nfib[i-2]+nfib[i-3];
        nfib[i]%=mod;
    }	
    cout<<nfib[n-1]<<endl;
}

signed main(){
	ios_base::sync_with_stdio(false);
    cin.tie(NULL);
	int t=1;
	cin>>t;
	while(t--){
		nFibonacci();
	}
	return 0;
}
