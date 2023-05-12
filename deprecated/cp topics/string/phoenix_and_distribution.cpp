// problem link : https://codeforces.com/problemset/problem/1348/C
// solution : below code

void solve(int t){
    //shree ganeshay namah
    int n;
    read(n);
    int k;
    read(k);
    string s;
    read(s);
    map<char,int> mp;
    F(i,0,n){
    	mp[s[i]]++;
    }
    if(mp.size()==1){
  		int freq=(n+k-1)/k;
  		string output;
  		F(i,0,freq) output+=s[0];
  		return println(output);
    }
    SORT(s);
    map<char,int> bp;
    F(i,0,k){
    	bp[s[i]]++;
    }
    // cout<<" bp s : "<<bp.size()<<endl;
    if(bp.size()>1){
    	string output;
    	output+=s[k-1];
    	return println(output);
    }else{
    	if(mp.size()>2){
    		string output=s.substr(k-1);
    		return println(output);	
    	}else{
    		if(s[k-1]==s[k]){
    			string output=s.substr(k-1);
    			return println(output);	
    		}else{
    			int freq=(mp[s[k]]+k-1)/k;
    			string output;
    			output+=s[k-1];
    			F(i,0,freq) output+=s[k];
    			return println(output);
    		}
    	}
    }
}   

