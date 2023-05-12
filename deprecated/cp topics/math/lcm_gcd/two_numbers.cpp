// problem link : https://www.codechef.com/problems/TWONUMBERS
// solution : below code

int gcdlcmdiff(int a,int b){
	return LCM(a,b)-GCD(a,b);
}
void solve(int t){
	//shree ganeshay namah
	int n;read(n);
	if(n<=2){
		cout<<0<<endl;
		return;
	}
	if(n%2){
		cout<<gcdlcmdiff(n/2,n/2 + 1)<<endl;
		return;
	}else{
		int half=n/2;
		if(half%2){
			cout<<gcdlcmdiff(half-2,half+2)<<endl;
			return;
		}else{
			cout<<gcdlcmdiff(half-1,half+1)<<endl;
			return;
		}
	}
}
