class Sieve{
public:
    vector<int> primes;
    
    vector<int> lp;
    int n=1e5+10;
    Sieve(){
        init();
    }
    Sieve(int n){
        this->n=n;
        init();
    }
    void init(){
        vector<bool> isprm(n,true);
        lp.assign(n,-1);
        
        isprm[0]=isprm[1]=false;
        for(int i=2;i<n;i++){
            if(isprm[i]==false) continue;
            lp[i]=i;
            primes.push_back(i);
            
            for(int j=i+i;j<n;j+=i){
                isprm[j]=false;
                if(lp[j]==-1){
                    lp[j]=i;
                }
                
            }
        }
    }
    vector<int> & get(){
        return primes;
    }
    int getLP(int num){
        return this->lp[num];
    }
    vector<int> getFactors(int num){
        
        set<int> factors;
        while(num>1){
            factors.insert(lp[num]);
            num/=lp[num];
        }
        vector<int> facts;
        for(auto & prm:factors) facts.push_back(prm);
        return facts;
    }
    void print(){
        for(auto &prm:primes) cout<<prm<<" ";cout<<endl;
    }
};
