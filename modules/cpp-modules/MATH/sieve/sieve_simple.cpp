class Sieve{
public:
    vi primes;

    int n=1e5+10;
    Sieve(){
        init();
    }
    Sieve(int n){
        this->n=n;
        init();
    }
    void init(){
        vb isprm(n,true);
        isprm[0]=isprm[1]=false;
        F(i,2,n){
            if(isprm[i]==false) continue;
            primes.pb(i);
            for(int j=i*i;j<n;j+=i){
                isprm[j]=false;
            }
        }

    }
    vi get(){
        return primes;
    }
    void print(){
        printv(primes);
    }
};
