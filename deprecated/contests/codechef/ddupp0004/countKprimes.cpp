#include<bits/stdc++.h>
#define int long long
#define endl "\n"
using namespace std;
int primeDivisors(int n){
	unordered_set<int> uns;
	int p=2;
	while(true){
		if(n>=p*p){
			if(n%p==0){
				uns.insert(p);
				n/=p;
			}else p++;
		}else{
			uns.insert(n);
			break;
		}
	}
	return uns.size();
}
int primeFactors[(int)(1e5+1)];
signed main(){
	int t=1;
	scanf("%lld",&t);
	for(int i=1;i<=100000;i++) primeFactors[i]=primeDivisors(i);
	while(t--){
		int a,b,k;
		cin>>a>>b>>k;
		int ctr=0;
		for(int i=a;i<=b;i++) if(primeFactors[i]==k) ctr++; cout<<ctr<<endl;
	}
	return 0;
}
