// problem link : https://codeforces.com/problemset/problem/235/A
// solution : below code

void solve(int t){
    //shree ganeshay namah
    int n;
    read(n);
    int a[3];
    int b[3];
    int c[3];
    F(i,0,3){
    	a[i]=max(1LL,n-i);
    	b[i]=max(1LL,n-i-1);
    	c[i]=b[i];
    }
    if(c[1]==n-2) c[1]=n;
    // println(a,3);
    // println(b,3);
    int first=LCM(a[0],a[1]);
    first=LCM(a[2],first);
    int second=LCM(b[0],b[1]);
    second=LCM(b[2],second);
    int third=LCM(c[0],c[1]);
    third=LCM(third,c[2]);
    int ans=max(first,second);
    ans=max(ans,third);
    println(ans);

}   
