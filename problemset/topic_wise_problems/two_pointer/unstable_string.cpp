// problem link : https://codeforces.com/problemset/problem/1535/C
// solution : below code

void solve(int t){
	//shree ganeshay namah
	string s;
	read(s);
	int n=s.size();
	int zero=-1;
	int one=-1;
	int l=0;
	int ctr=0;
	F(i,0,n){
		if(s[i]=='0'){
			if(zero != -1 && (i-zero)%2==1){
				l=max(l,zero+1);
			}
			if(one != -1 && (i-one)%2==0){
				l=max(l,one+1);
			}
			ctr+=i-l+1;
			zero=i;
		}else if(s[i]=='1'){
			if(one != -1 && (i-one)%2==1){
				l=max(l,one+1);
			}
			if(zero != -1 && (i-zero)%2==0){
				l=max(l,zero+1);
			}
			ctr+=i-l+1;
			one=i;
		}else{
			ctr+=i-l+1;
		}
	}
	println(ctr);
	// print answers here

}
