// problem link : https://codeforces.com/problemset/problem/1470/A
// solution : below code

void solve(int t){
    //shree ganeshay namah  
    int n,k;
    read(n,k);
    vi v(n);
    readv(v);
    vi pref(n,0);
    pref[0]=v[0];
    F(i,1,n){
        pref[i]=pref[i-1]+v[i];
    }
    int mx=0;
    F(i,1,n){
        int diff=((100*v[i]+k-1)/k)-pref[i-1];
        mx=max(mx,diff);
    }
    println(mx);
    // kick(t);
    
    // write your answer here
    
    //complete your answer here
    // println();
}   
