// problem link : https://codeforces.com/problemset/problem/459/A
// solution : below code
// time taken : 15 m 33 s


void solve(int t){
	//shree ganeshay namah
	int a,b,c,d;read(a,b);read(c,d);
	int x,y,z,w;
	// print(a,b);print(c,d);println();
	if(a==c || b==d){
		//on same side
		int diff=0;
		if(a==c){
			diff=b-d;
			x=a+diff,z=c+diff,y=b,w=d;
		}else{
			diff=a-c;
			x=a,z=c,y=b+diff,w=d+diff;
		}

	}else{
		//on diagonal
		if(abs(a-c)==abs(b-d)){
			x=a,y=d,z=c,w=b;
		}else{
			cout<<-1;
			println();
			return;
		}
	}
	print(x,y);print(z,w);
	println();

}
