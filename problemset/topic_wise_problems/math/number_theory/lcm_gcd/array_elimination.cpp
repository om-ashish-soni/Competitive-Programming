// problem link : https://codeforces.com/problemset/problem/1601/A
// solution : below code

#define GCD(a,b) (__gcd((a),(b)))

void findAllFactors(int n,std::vector<int>& factors){

    double sqroot=sqrt(n);
    factors.push_back(1);
    if(n<=1){
        return;     
    }
    for(int i=2;i<=sqroot;i++){
        if(n%i == 0){
            factors.push_back(i);
            if(n/i != i){
                factors.push_back(n/i);
            }
        }
    }
    factors.push_back(n);
    sort(factors.begin(),factors.end());
}

void solve(int t){
    //shree ganeshay namah  
    int n;
    read(n);
    vi v(n);
    readv(v);

    int sm=0;
    F(i,0,n) sm+=v[i];
    if(sm==0){
        F(i,1,n+1) cout<<i<<" ";cout<<endl;
        return;
    }
    vector<int> bits(32,0);
    F(i,0,n){
        int num=v[i];
        bitset<32> bs(num);
        F(k,0,32){
            if(bs[k]==1) bits[k]++;
        }
    }
    int mygcd=0;
    F(i,0,32){
        int freq=bits[i];
        mygcd=GCD(mygcd,freq);
    }
    vi factors;
    findAllFactors(mygcd,factors);
    printv(factors);
    // kick(t);
    
    // write your answer here
    
    //complete your answer here
    // println();
}   
    
