// modulo arithmetic 
pair<int,int> extended_gcd(int a,int b){
	if(b==0) return{1,1};
	pair<int,int> pr=extended_gcd(b,a%b);
	return {pr.second,pr.first-(a/b)*pr.second};
}
int power(long long x, unsigned int y, int p) 
{ 
    int res = 1; 
    x = x % p; // Update x if it is more than or 
    if (x == 0) return 0; // In case x is divisible by p;
    while (y > 0) { 
        if (y & 1) res = (res*x) % p; 
        y = y>>1; // y = y/2 
        x = (x*x) % p; 
    } 
    return res; 
} 
int modSub(int a,int b,int mod){
	return ((a%mod - b%mod + mod)%mod);
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
