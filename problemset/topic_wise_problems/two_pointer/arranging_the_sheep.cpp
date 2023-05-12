// problem link : https://codeforces.com/problemset/problem/1520/E
// solution : below code

void solve(int t){
	//shree ganeshay namah
	int n;
	read(n);
	string s;
	read(s);
	int l=0,r=0;
	int left=0,right=0;
	F(i,0,n){
		if(s[i]=='*'){
			l=i;
			break;
		}
	}
	FND(i,n-1,0){
		if(s[i]=='*'){
			r=i;
			break;
		}
	}
	vi v;
	F(i,l+1,r){
		if(s[i]=='.'){
			v.pb(i);
		}
	}
	int sz=v.size();
	int li=0;
	int ri=sz-1;
	int ctr=0;
	// cout<<"l : "<<l<<" , r : "<<r<<endl;
	// printv(v);
	while(li<=ri){
		// cout<<"li : "<<li<<" , ri : "<<ri<<endl;
		// cout<<"l : "<<l<<" , vs "<<v[li]<<endl;
		while(l<v[li]){
			if(s[l]=='*') left++;
			l++;
		}
		// cout<<"r : "<<r<<" , vs : "<<v[ri]<<endl;
		while(r>v[ri]){
			if(s[r]=='*') right++;
			r--;
		}
		if(left<right){
			li++;
			ctr+=left;
		}else{
			ri--;
			ctr+=right;
		}
		// cout<<"after : "<<"li : "<<li<<", ri : "<<ri<<endl;
	}
	println(ctr);
	// print answers here

}
