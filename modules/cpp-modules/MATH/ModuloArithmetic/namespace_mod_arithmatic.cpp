namespace ModuloArithmetic{
    pair<int,int> extended_gcd(int a,int b){
        if(b==0) return{1,1};
        pair<int,int> pr=extended_gcd(b,a%b);
        return {pr.second,pr.first-(a/b)*pr.second};
    }
    int hcf(int a,int b){
        if(a==0 || b==0) return max(a,b);
        pair<int,int> pr=extended_gcd(a,b);
        return (a*pr.first + b*pr.second);
    }
    int lcm(int a,int b){
        return (a*b)/(__gcd(a,b));
    }
    int gcd(int a,int b){
        return __gcd(a,b);
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
    int get_primitive_root (int p) {
        vector<int> fact;
        int phi = p-1,  n = phi;
        for (int i=2; i*i<=n; ++i)
            if (n % i == 0) {
                fact.push_back (i);
                while (n % i == 0)
                    n /= i;
            }
        if (n > 1)
            fact.push_back (n);

        for (int res=2; res<=p; ++res) {
            bool ok = true;
            for (size_t i=0; i<fact.size() && ok; ++i)
                ok &= power (res, phi / fact[i], p) != 1;
            if (ok)  return res;
        }
        return -1;
    }
    int get_root_power(long long num){
        vector<long long> powers(63);
        for(int i=0;i<63;i++){
            powers[i]=(1LL<<i);
        }
        for(int i=62;i>=0;i--){
            if(num%powers[i]==1) return i;
        }
        return -1;
    }
};