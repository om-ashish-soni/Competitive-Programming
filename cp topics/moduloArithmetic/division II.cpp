// Prolbem link : https://practice.geeksforgeeks.org/problems/division-ii/0/
// solution below code
pair<int,int> extended_gcd(int a,int b){
	if(b==0) return{1,1};
	pair<int,int> pr=extended_gcd(b,a%b);
	return {pr.second,pr.first-(a/b)*pr.second};
}
int modMul(int a,int b,int mod){
	return ((a%mod)*(b%mod))%mod;
}
int modAdd(int a,int b,int mod){
	return ((a%mod)+(b%mod))%mod;
}
int modInv(int a,int mod){
	int x,y;
	pair<int,int> pr=extended_gcd(a,mod);
	x=pr.first;
	y=pr.second;
	int g=(a*x + mod*y);
	if(g!=1){
		cerr<<"modular inverse does not exist , gcd != 1"<<endl;
		exit(0);
	}
	// adding m to avoid negative value of x 
	int res=(x%mod + mod)%mod;
	return res;
}
int modDiv(int a,int b,int mod){
	
	a=a%mod;
	int inv=modInv(b,mod);
	int res=(inv*a)%mod;
	return res;
}
void solve(){
	int a,b,c,n;
	cin>>a>>b>>c>>n;
	int mod=1e9+7;
	int res=a;
	for(int i=0;i<n;i++){
		res=modAdd((modMul(modDiv(res,b,mod),c,mod)),-1,mod)%mod;
	}
	if(res<0) res=(res%mod + mod)%mod;
	cout<<res<<endl;
}
