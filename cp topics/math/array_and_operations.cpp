// problem link : https://codeforces.com/problemset/problem/1618/D
// solution : below code

void solve(int t){
    //shree ganeshay namah  
    int n;
    read(n);
    int k;
    read(k);
    vi v(n);
    readv(v);
    SORT(v);
    REVERSE(v);
    int l=0;
    int r=2*k-1;
    int sm=0;
    while(l<r){
        int first=l;
        int next=l+k;
        sm+=v[next]/v[first];
        v[first]=0;
        v[next]=0;
        l++;
        r--;
    }
    F(i,0,n){
        sm+=v[i];
    }
    println(sm);
    // kick(t);
    
    // write your answer here
    
    //complete your answer here
    // println();
}   
