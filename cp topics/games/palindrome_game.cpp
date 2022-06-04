// problem link : https://codeforces.com/problemset/problem/445/A
// solution : below code
  
void solve(int t){
	//shree ganeshay namah
	int n;
	read(n);
	string s;
	read(s);
	int ones=count(ALL(s),'1');
	int zeros=n-ones;
	
	if(n%2==0) println("BOB");
	else{
		int ap=0,bp=0;
		if(s[n/2]=='0'){
			ap=1;
			bp=zeros-1;
		}else{
			ap=zeros;
			bp=0;
		}
		if(ap==bp) println("DRAW");
		else if(ap>bp) println("BOB");
		else println("ALICE");
	}
}
