class Factorial{
    public:
    vector<long long> fact;
    long long mod=(1e9)+7;
    long long sz=0;
    Factorial(long long n,long long mod=(int)(1e9+7)){
        this->sz=n+10;
        this->fact.resize(sz);
        this->mod=mod;
        init();
    }
    void init(){
        fact[0]=1;
        for(int i=1;i<sz;i++){
            fact[i]=((fact[i-1]%mod)*(i%mod))%mod;
        }
    }
    long long get(int n){
        return this->fact[n];
    }
};
