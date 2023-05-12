vector<int> pals;
map<int,bool> isPal;
bool isPalindrome(string &s){
	string copy=s;
	reverse(begin(copy),end(copy));
	return s==copy;
}
string intToString(int n){
	ostringstream ostr;
	ostr<<n;
	return ostr.str();
}
bool isPalindromeNumber(int n){
	return isPalindrome(intToString(n));
}
void kickinit(){
	int MAX_LIMIT=1e5 + 10;
	for(int i=1;i<=MAX_LIMIT;i++){
		if(isPalindromeNumber(i)){
			pals.push_back(i);
			isPal[i]=true;
		}
	}
}
void printKickStartCase(int t){
	cout<<"Case #"<<t<<": ";
}
void solve(int t){
	
	int n;cin>>n;
	int ctr=0;
	int MAX_LIMIT=1e5 + 10;
	vi factors;
	findAllFactors(n,factors);
	for(auto num:factors){
		if(isPalindromeNumber(num)) ctr++;
	}
	//utility
	printKickStartCase(t);
	// print answers here
	cout<<ctr<<endl;
}
signed main(){     
	
	ios_base::sync_with_stdio(false);
    cin.tie(NULL);
// #ifndef ONLINE_JUDGE
//     freopen("input.txt", "r", stdin);
//     freopen("error.txt", "w", stderr);
//     freopen("output.txt", "w", stdout);
// #endif
	// seive();
	// seiveWithHPLP();
	// seiveWithAllFactors();
	// seiveWithAllPrimes();
	kickinit();

	int t=1;
	cin>>t;

	for(int i=0;i<t;i++){
		solve(i+1);
	}
	cerr<<"time taken : "<<(float)clock()/CLOCKS_PER_SEC<<" secs"<<endl;
	return 0;
}
