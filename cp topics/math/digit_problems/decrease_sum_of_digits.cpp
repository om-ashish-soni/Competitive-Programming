// problem link : https://codeforces.com/problemset/problem/1409/D
// solution : below code

int dtos(int n){
    vi v;
    while(n>0){
        v.pb(n%10);
        n/=10;
    }
    int mult=1;
    int sz=v.size();
    int total=accumulate(ALL(v),0);
    return total;
}

void solve(int t){
    int n;
    read(n);
    int limit;
    read(limit);
    
    int base=1;
    int ctr=0;
    while(dtos(n)>limit){
        // cout<<"dtos : "<<dtos(n)<<" , limit : "<<limit<<endl;
        int digit=(n/base)%10;
        if(digit>0){
            int addon=(10-digit)*base;
            n+=addon;
            ctr+=addon;
        }
        base*=10;
    }
    println(ctr);
}
