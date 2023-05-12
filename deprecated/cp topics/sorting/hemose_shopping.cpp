// problem link : https://codeforces.com/problemset/problem/1592/B
// solution : below code

void solve(int t){
    //shree ganeshay namah  
    int n;
    read(n);
    int x;
    read(x);
    vi v(n);
    readv(v);
    vi sorted=v;
    SORT(sorted);
    F(i,0,n){
        if(v[i] != sorted[i]){
            int diff=max(i,n-i-1);
            if(x>diff){
                YESNO1(false);
                return;
            }
        }
    }
    YESNO1(true);
    return;
    // kick(t);
    
    // write your answer here
    
    //complete your answer here
    // println();
}   
