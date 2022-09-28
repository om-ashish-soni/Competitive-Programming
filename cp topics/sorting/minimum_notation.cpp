// problem link : https://codeforces.com/contest/1730/problem/C
// solution : below code

void solve(int t){
	//shree ganeshay namah
	//println("shree ganeshay namah");
	string s;
	read(s);
	char mn='9';
	int n=s.size();
	string op;
	FND(i,n-1,0){
		if(s[i]>mn){
			char c=s[i];
			if(c<'9') c++;
			op+=c;
		}
		else{
			op+=s[i];
			mn=min(mn,s[i]);
		}
	}
	SORT(op);
	println(op); 	
	// print answers here

}
