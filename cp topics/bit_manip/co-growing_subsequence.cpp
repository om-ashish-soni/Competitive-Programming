// problem link : https://codeforces.com/problemset/problem/1547/D
// solution : below code


int getcost(vi & v1,vi & v2){
    if(v1.size() != v2.size()) return LLONG_MAX;
    int n=v1.size();
    int cost=0;
    F(i,0,n){
        cost+=abs(v1[i]-v2[i]);
    }
    return cost;
}

void solve(int t){
    //shree ganeshay namah  
    int n;
    read(n);
    vi v(n);
    readv(v);
    vi sol={0};
    F(i,1,n){
        bitset<32> bs1(v[i-1]),bs2(v[i]);
        int addon=0;
        F(k,0,32){
            if(bs1[k]==1 && bs2[k]==0){
                addon+=(1LL<<k);
            }
        }
        sol.pb(addon);
        v[i]+=addon;
    }
    printv(sol);
    // kick(t);
    
    // write your answer here
    
    //complete your answer here
    // println();
}   
