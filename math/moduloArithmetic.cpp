
// modulo arithmetic 
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
int modMul(int a,int b,int mod){
	return ((a%mod)*(b%mod))%mod;
}
int modAdd(int a,int b,int mod){
	return ((a%mod)+(b%mod))%mod;
}
