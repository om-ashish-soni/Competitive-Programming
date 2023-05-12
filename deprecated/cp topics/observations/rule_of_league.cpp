// problem link : https://codeforces.com/problemset/problem/1733/B
// solution : below code

void solve(int t){
	//shree ganeshay namah
	int n;
	read(n);
	int a,b;
	read(a,b);
	if(a != 0 && b==0 && (n-1)%a==0){
		int x=(n-1)/a;
		int person=1;
		bool flag=true;
		F(i,0,x){
			F(j,0,a) print(person);
			person+=a;
			if(flag){
				person++;
				flag=false;
			}
		}			
		println();
		return;
	}
	if(a==0 && b != 0 && (n-1)%b==0){
		int y=(n-1)/b;
		int person=1;
		bool flag=true;
		F(i,0,y){
			F(j,0,b) print(person);
			person+=b;
			if(flag){
				person++;
				flag=false;
			}
		}
		println();
		return;
	}
	return reject();
	// print answers here


}
