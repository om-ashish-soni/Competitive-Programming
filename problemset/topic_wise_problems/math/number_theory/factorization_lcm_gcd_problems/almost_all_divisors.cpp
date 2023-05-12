// problem link : https://codeforces.com/problemset/problem/1165/D
// solution : below code

void solve(int t){
    int n;
    read(n);
    vi v(n);
    readv(v);
    SORT(v);
    int com=v.front()*v.back();
    vi factors;
    findAllFactors(com,factors);

    v.push_back(1);
    v.pb(com);
    SORT(v);
    if(v==factors) return println(com);
    // printv(v);
    // printv(factors);
    return reject();
    
}