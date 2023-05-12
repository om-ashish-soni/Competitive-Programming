// problem link : https://codeforces.com/problemset/problem/515/C
// solution : below code

int c2i(char c){
	return c-'0';
}
void solve(int t){
	//shree ganeshay namah
	int n;
	read(n);
	string s;
	read(s);
	vvi hash(10);
	vi v(10,0);
	hash[2]={2};
	hash[3]={3};
	hash[4]={3,2,2};
	hash[5]={5};
	hash[6]={5,3};
	hash[7]={7};
	hash[8]={7,2,2,2};
	hash[9]={7,3,3,2};
	FEACH(c,s){
		if(c>'1'){
			int val=c2i(c);
			// cout<<"val : "<<val<<endl;
			FEACH(num,hash[val]){
				// cout<<num<<" ";
				v[num]++;
			}
			// cout<<endl;
		}
	}
	FND(i,9,2){
		F(j,0,v[i]){
			cout<<i;
		}
	}
	println();

}
