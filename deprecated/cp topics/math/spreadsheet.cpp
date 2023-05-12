// problem link : https://codeforces.com/problemset/problem/1/B
// solution : below code

bool isnum(char c){
	return c-'A' < 0;
}
void numToColumn(string num){
	int nm;
	stringstream str(num);
	str>>nm;
	stack<char> stk;
	while(nm>0){
		stk.push((nm-1)%26+'A');
		nm--;
		nm/=26;
	}
	while(stk.size()>0){
		cout<<stk.top();stk.pop();
	}
}
void front(string s){
	string row;
	int n=s.size();
	int stop=-1;
	for(int i=1;i<n;i++){
		if(s[i]=='C'){
			stop=i;
			break;
		}
		row+=s[i];
	}
	string col;
	for(int j=stop+1;j<n;j++){
		col+=s[j];
	}
	numToColumn(col);
	cout<<row;
	cout<<endl;
}
void columnToNum(string num){
	int n=num.size();
	int mul=1;
	int nm=0;
	for(int i=n-1;i>=0;i--){
		nm+=(num[i]-'A'+1)*mul;
		mul*=26;
	}
	cout<<nm;
}
void reverse(string s){
	string col;

	int n=s.size();
	int stop=-1;
	for(int i=0;i<n;i++){
		if(isnum(s[i])){
			stop=i;
			break;
		}
		col+=s[i];
	}
	cout<<'R';
	for(int i=stop;i<n;i++) cout<<s[i];
	cout<<'C';
	columnToNum(col);
	cout<<endl;
}
void solve(int t){
	string s;cin>>s;
	if(s[0]=='R' and isnum(s[1]) and s.find('C') != -1) front(s);
	else reverse(s);
}
