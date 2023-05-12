// problem link : https://codeforces.com/contest/1700/problem/B
// solution : below code

void solve(int t){
    //shree ganeshay namah
    int n;
    read(n);
    string s;
    read(s);
    int borrow=0;
    if(s[0]=='9'){
    	FND(i,n-1,0){
    		int diff='1'-s[i]-borrow;
    		// cout<<s[i]<<" "<<diff<<endl;
    		if(diff<0){
    			s[i]='0'+(10+diff);
    			borrow=1;
    		}else{
    			s[i]='0'+diff;
    			borrow=0;
    		}
    	}
    }else{
    	F(i,0,n){
    		s[i]='0'+'9'-s[i];
    	}
    }
    println(s);
}   
