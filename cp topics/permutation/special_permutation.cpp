// problem link : https://codeforces.com/problemset/problem/1352/G
// solution : below code

void solve(int t){
    //shree ganeshay namah
    int n;
    read(n);
    if(n<4) return reject();
    if(n==4){
    	cout<<3<<" "<<1<<" "<<4<<" "<<2<<endl;
    	return;
    }
    int lastodd=n;
    if(n%2==0) lastodd--;
    int odd=1;
    while(odd<=lastodd){
    	print(odd);
    	odd+=2;
    }
    int even1=lastodd-3;
    while(even1>=2){
    	print(even1);
    	even1-=4;
    }
    int mod=abs(even1%4);
    // cout<<endl<<even1<<" "<<mod<<" : "<<endl;
    if(mod==2){
    	even1+=6;
    }else if(mod==0){
    	even1+=2;
    }
    while(even1<=n){
    	print(even1);
    	even1+=4;
    }
    if(n%2==0) cout<<n;
    println();
}   
