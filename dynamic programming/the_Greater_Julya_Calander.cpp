// problem link : 
// solution : below code


map<int,int> memo;
int getMax(int n){
    ostringstream ostr;
    ostr<<n;
    int mx=0;
    string num=ostr.str();
    for(auto c:num){
        mx=max(mx,(int)(c-'0'));
    }
    return mx;
}
int doit(int n){
    if(n<=0) return 0;
    if(memo.count(n)) return memo[n];
    int total=0;
    total=1+doit(n-getMax(n));
    memo[n]=total;
    return total;
}
void solve(){
    int n;cin>>n;
    cout<<doit(n)<<endl;
}   
