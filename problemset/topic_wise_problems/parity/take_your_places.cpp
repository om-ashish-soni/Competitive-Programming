// problem link : https://codeforces.com/problemset/problem/1556/B
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
    int evens=0;
    int odds=0;
    int ee=0;
    int eo=0;
    int oe=0;
    int oo=0;
    F(i,0,n){
        if(v[i]%2==0){
            evens++;
            if(i%2) eo++;
            else ee++;
        }else{
            odds++;
            if(i%2) oo++;
            else oe++;
        }
    }
    int limit=(n+1)/2;
    if(odds>limit || evens>limit){
        return reject();
    }
    int cost=LLONG_MAX;
    
    vi v_odd,v_even;
    F(i,0,n){
        if(v[i]%2==i%2){
            if(v[i]%2) v_odd.pb(i);
            else v_even.pb(i);
        }
    }
    cost=min(cost,getcost(v_odd,v_even));
    v_odd.clear();
    v_even.clear();
    F(i,0,n){
        if(v[i]%2!=i%2){
            if(v[i]%2) v_odd.pb(i);
            else v_even.pb(i);
        }
    }
    cost=min(cost,getcost(v_odd,v_even));
    println(cost);
    // kick(t);
    
    // write your answer here
    
    //complete your answer here
    // println();
}   
    
