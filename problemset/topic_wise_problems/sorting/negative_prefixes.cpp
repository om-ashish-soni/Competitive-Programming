// problem link : https://codeforces.com/contest/1418/problem/B
// solution : below code


void solve(int t){
    //shree ganeshay namah  
    int n;
    read(n);
    vi v(n);
    readv(v);
    vi bits(n);
    readv(bits);
    vi unblock;
    F(i,0,n){
        if(bits[i]==0) unblock.pb(v[i]);
    }
    SORT(unblock);
    REVERSE(unblock);
    int index=0;
    F(i,0,n){
        if(bits[i]==0){
            v[i]=unblock[index];
            index++;
        }
    }
    printv(v);
    // kick(t);
    
    // write your answer here
    
    //complete your answer here
    // println();
}   
