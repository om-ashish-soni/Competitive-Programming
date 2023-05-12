// problem link : https://codeforces.com/problemset/problem/1355/B
// solution : below code

void solve(int t){
	//shree ganeshay namah
	int n;
	read(n);
	int a[n];
	read(a,n); 
	SORTA(a,n);
	int group=0;
	int index=0;
	int content=0;
	F(i,0,n){
		if(content+1>=a[i]){
			group++;
			content=0;
		}else{
			content++;
		}
	}
	println(group);
}
