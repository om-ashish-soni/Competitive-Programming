// problem link : https://codeforces.com/problemset/problem/1344/A
// solution : below code

void solve(int t){
    //shree ganeshay namah
    int n;
    read(n);
    int a[n];
    read(a,n);
    vi v(n,1);
    F(i,0,n){
    	int num=a[i];
    	int next=((i+a[i])%n + n)%n;
    	v[i]--;
    	v[next]++;
    }
    bool flag=true;
    F(i,0,n){
    	if(v[i]==0){
    		flag=false;
    		break;
    	}
    }
    YESNO1(flag);
}   
