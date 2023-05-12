// problem link : https://codeforces.com/problemset/problem/1349/A
// solution : below code

void solve(int t){
    //shree ganeshay namah
    int n;
    read(n);
    vi a(n);
    readv(a);
    vi seg(4*n,0);
    char op='g';
    buildseg(seg,a,0,0,n-1,op);
    vi v;
    F(i,0,n){
    	int l,r;
    	l=0;r=i-1;
    	int first=getseg(seg,0,0,n-1,l,r,op);	
    	l=i+1;r=n-1;
    	int second=getseg(seg,0,0,n-1,l,r,op);
    	int tmp=GCD(first,second);
    	v.pb(tmp);
    }
    int ans=v[0];
    F(i,0,n){
    	ans=LCM(ans,v[i]);
    }
    println(ans);
}   
