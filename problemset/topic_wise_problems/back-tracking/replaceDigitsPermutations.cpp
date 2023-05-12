// Problem link : https://practice.geeksforgeeks.org/problems/digit-combination/0/
// solution : below code

#include<bits/stdc++.h>
#define int long long
#define endl "\n"
using namespace std;
bool isDigit(char &ch){
    return (ch-48>=0 && ch-48<=9);
}
void replaceDigitsWithSpecialChars(string s,int index){
    if(index>=s.size()){
        cout<<s<<" ";
        return;
    }
    if(isDigit(s[index])){
        s[index]='!';
        replaceDigitsWithSpecialChars(s,index+1);    
        s[index]='*';
        replaceDigitsWithSpecialChars(s,index+1);    
        s[index]='@';
    }
    return replaceDigitsWithSpecialChars(s,index+1);
}
void solve(){
	string s;
	cin>>s;
	int index=0;
	replaceDigitsWithSpecialChars(s,index);
	cout<<endl;
}

signed main(){
	ios_base::sync_with_stdio(false);
    cin.tie(NULL);
//#ifndef ONLINE_JUDGE
//    freopen("input.txt", "r", stdin);
//    freopen("error.txt", "w", stderr);
//    freopen("output.txt", "w", stdout);
//#endif
	int t=1;
	cin>>t;
	while(t--){
		solve();
	}
	//cerr<<"time taken : "<<(float)clock()/CLOCKS_PER_SEC<<" secs"<<endl;
	return 0;
}
