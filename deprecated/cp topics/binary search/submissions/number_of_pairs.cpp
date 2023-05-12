// problem link : https://codeforces.com/problemset/problem/1538/C
// solution : below code

void solve(int t){
    //shree ganeshay namah  
    int n;
    read(n);
    int l,r;
    read(l,r);
    vi v(n);
    readv(v);
    SORT(v);
    int ctr=0;
    F(i,0,n){
        int num=v[i];
        int index1=lower_bound(v.begin()+i+1,v.end(),l-num)-v.begin();
        if(index1<n){
            int index2=upper_bound(v.begin()+i+1,v.end(),r-num)-v.begin();
            ctr+=index2-index1;
        }
    }
    println(ctr);
    // kick(t);
    
    // write your answer here
    
    //complete your answer here
    // println();
}   
