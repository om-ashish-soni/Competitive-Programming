// problem link : https://codeforces.com/problemset/problem/1717/C
// solution : below code

void solve(int t){
    //shree ganeshay namah  
    int n;
    read(n);
    vi v1(n),v2(n);
    readv(v1);
    readv(v2);
    F(i,0,n){
        int next=(i+1)%n;
        if(v1[i] > v2[i]){
            YESNO1(false);
            return;
        }
        if(v1[i]<v2[i]){
            if(v2[i]-v2[next]>1){
                YESNO1(false);
                return;
            }
        }
    }
    YESNO1(true);
    // kick(t);
    
    // write your answer here
    // println(pref);
    
    //complete your answer here
    // println();
}   
