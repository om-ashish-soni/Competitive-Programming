#include<bits/stdc++.h>
#define int long long
#define endl "\n"
using namespace std;
void yes(){
	cout<<"YES"<<endl;
}
void no(){
	cout<<"NO"<<endl;
}
int bitwiseAnd(int *arr,int start,int end,int andd){
	// cout<<"takend : "<<endl;
	for(int i=start;i<=end;i++){
		// cout<<arr[i]<<" ";
		andd=(andd & arr[i]);
	}
	cout<<endl;
	return andd;
}
static bool comp(pair<int,int>& p1,pair<int,int>& p2){
	return p1.second>p2.second;
}
void judge(string &s){
	int snk=count(s.begin(),s.end(),'s');
	int n=s.size();
	int mng=count(s.begin(), s.end(),'m');
	// cout<<snk<<" "<<mng<<endl;
	if(snk==mng){
		cout<<"tie";
	}else if(snk>mng){
		cout<<"snakes";
	}else{
		cout<<"mongooses";
	}
	cout<<endl;
}
void solve(){
	string s;
	cin>>s;
	if(s.size()==1) return judge(s);
	if(s[0]=='m'){
		if(s[1]=='s') s[1]='.';
	}
	for(int i=1;i<s.size();i++){
		if(s[i]=='m'){
			if(s[i-1]=='s'){
				s[i-1]='.';
			}else if(i+1<s.size() && s[i+1]=='s'){
				s[i+1]='.';
			}
		}
	}
	return judge(s);
}
signed main(){
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	int t=1;
	cin>>t;
	while(t--){
		solve();
	}
}
