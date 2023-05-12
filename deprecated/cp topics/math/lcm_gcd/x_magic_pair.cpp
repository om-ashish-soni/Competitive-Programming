// problem link : https://codeforces.com/problemset/problem/1612/D
// solution : below code

void solve(int t){
	//shree ganeshay namah
	int a,b,x;
	read(a,b);
	read(x);
	if(a<b) swap(a,b);
	if(x>max(a,b)){
		YESNO1(false);
		return;
	}
	while(a>0 && b>0){
		// cout<<a<<" vs "<<b<<endl;
		if(x==a || x==b){
			YESNO1(true);
			return;
		}
		else if(x>a){
			YESNO1(false);
			return;
		}
		else if(x>=b && x<=a){
			if(x%b == a%b){
				YESNO1(true);
				return;
			}else{
				YESNO1(false);
				return;
			}
		}else{
			int last_b=b;
			b=a%b;
			a=last_b;
		}

	}
	
	YESNO1(false);
	return;
	// print answers here

}
