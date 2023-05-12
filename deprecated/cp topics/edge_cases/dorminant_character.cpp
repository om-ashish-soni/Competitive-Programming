// problem link : https://codeforces.com/problemset/problem/1605/C
// solution : below code

void solve(int t){
	//shree ganeshay namah
	int n;
	read(n);
	string s;
	read(s);
	vi a(n,0),b(n,0),c(n,0);
	vi v;
	int mn=LLONG_MAX;
	F(i,0,n){
		if(i-1>=0){
			a[i]=a[i-1];
			b[i]=b[i-1];
			c[i]=c[i-1];
		}
		if(s[i]=='a'){
			//
			a[i]++;
			int sz=v.size();
			int permit=3;
			FND(j,sz-1,0){
				int index=v[j];
				int a_f=a[i]-a[index]+1;
				int b_f=b[i]-b[index];
				int c_f=c[i]-c[index];
				if(max(b_f,c_f)>a_f){
					break;
				}else if(max(b_f,c_f)<a_f){
					mn=min(mn,i-index+1);
				}
				permit--;
				if(permit<0){
					break;
				}
			}
			//
			v.pb(i);
			
		}else if(s[i]=='b'){
			b[i]++;
		}else{
			c[i]++;
		}

	}
	if(mn==LLONG_MAX){
		return reject();
	}
	println(mn);

	//utility
	// printKickStartCase(t);
	// print answers here

}
