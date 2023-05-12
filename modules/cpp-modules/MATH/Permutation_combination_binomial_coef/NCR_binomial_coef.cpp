// some modulo functions needed for computation 
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

// actual code for NCR , tc: O(N)
class NCR{
	public : 
	int mod=-1;
	int n,r,res=1;
	void computeNcr(){
		if(r>n){
			res=0;
			return;
		}
		for(int i=0;i<r;i++){
			res*=(n-i);
			res/=(i+1);
		}
	}
	void computeNcrMod(){
		if(r>n){
			res=0;
			return;
		}
		for(int i=0;i<r;i++){
			res=modMul(res,n-i,mod);
			res=modDiv(res,i+1,mod);
		}
	}
	NCR(int n,int r):n(n),r(r){
		if(r>n-r) r=n-r;
		this->computeNcr();
	}
	NCR(int n,int r,int mod):n(n),r(r),mod(mod){
		if(r>n-r) r=n-r;
		this->computeNcrMod();
	}
	int get(){
		return res;
	}
};
void solve(){
	int n(6),r(5),mod(1e9+7);
	NCR ncr=*new NCR(n,r,mod);
	cout<<ncr.get();
	cout<<endl;
}
