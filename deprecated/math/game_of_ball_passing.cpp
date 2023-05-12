// problem link : https://codeforces.com/problemset/problem/1649/B
// solution : below code

void solve(int t){
    //shree ganeshay namah  
    int n;
    read(n);
    vi v(n);
    readv(v);
    int sm=0;
    F(i,0,n){
        sm+=v[i];
    }
    if(sm==0){
        cout<<0<<endl;
        return;
    }
    F(i,0,n){
        if(v[i]>sm-v[i]){
            int ans=v[i]-(sm-v[i]);
            println(ans);
            return;
        }
    }
    cout<<1<<endl;
    return;
    // kick(t);
    
    // write your answer here
    
    //complete your answer here
    // println();
}   
