// problem link : https://codeforces.com/problemset/problem/1369/B
// solution : below code

void solve(int t){
	//shree ganeshay namah
	int n;
	read(n);
	string s;
	read(s);
	int firstone=-1,lastzero=-1;
	F(i,0,n){
		if(s[i]=='1'){
			firstone=i;
			break;
		}
	}
	if(firstone!=-1){
		FND(i,n-1,firstone){
			if(s[i]=='0'){
				lastzero=i;
				break;
			}
		}
	}
	if(firstone==-1){
		println(s);
		return;
	}else if(lastzero==-1){
		println(s);
		return;
	}else{
		string ans;
		F(i,0,firstone) ans+='0';
		ans+='0';
		F(i,lastzero+1,n) ans+='1';
		println(ans);
	}
}
