// problem link : https://codeforces.com/problemset/problem/1352/B
// solution : below code
// time taken : 13 m 37 s

void solve(int t){
	//shree ganeshay namah
	int n,k;
	read(n,k);
	bool flag=true;
	if(n%2){
		if(k>n || k%2==0){
			YESNO1(false);
		}
		else{
			YESNO1(true);
			F(i,0,k-1){
				cout<<1<<" ";
				n--;
			}
			cout<<n<<endl;
		}
	}else{
		if(k*2>n){
			if(k>n || k%2==1){
				YESNO1(false);
			}else{
				YESNO1(true);
				F(i,0,k-1){
					cout<<1<<" ";
					n--;
				}
				cout<<n<<endl;
			}
		}else{
			YESNO1(true);
			F(i,0,k-1){
				cout<<2<<" ";
				n-=2;
			}
			cout<<n<<endl;
		}
	}

}
