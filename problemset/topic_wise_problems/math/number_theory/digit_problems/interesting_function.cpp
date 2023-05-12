// problem link : https://codeforces.com/problemset/problem/1538/F
// solution : below code


int get(int a){
    int limit=1e9+10;
    int ctr=0;
    int base=1;
    while(base<limit){
        ctr+=a/base;
        base*=10;
    }
    return ctr;
}
void solve(int t){
    int a,b;
    read(a,b);
    int first=get(a);
    int second=get(b);
    int delta=second-first;
    println(delta);
}