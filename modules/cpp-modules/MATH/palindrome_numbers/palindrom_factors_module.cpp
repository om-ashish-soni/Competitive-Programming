vector<int> pals;
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
	for(int i=1;i<MAX_LIMIT;i++){
		if(isPalindromeNumber(i)){
			pals.push_back(i);
		}
	}
}
