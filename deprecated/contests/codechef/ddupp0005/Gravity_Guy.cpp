#include<bits/stdc++.h>
#define int long long
#define endl "\n"
using namespace std;

vector<int> memo1;
vector<int> memo2;
vector<string> lane(2);
int selectMin(int no_of_transition,int ctr){
	if(no_of_transition==-1) return ctr;
	if(ctr==-1) return no_of_transition;
	return min(no_of_transition,ctr);
}
int selectMinWithTransition(int no_of_transition,int ctr){
	if(ctr==-1) return no_of_transition;
	if(no_of_transition==-1) return 1+ctr;
	return min(no_of_transition,ctr+1);
}
int canReach(int lane_no,int index,bool tran=false){
	if(index>=lane[0].size()) return 0;
	if(lane[lane_no][index]=='#') return -1;
	vector<int>& memo=(lane_no)?(memo2):(memo1);
	if(memo[index] != -1) return memo[index];
	int no_of_transition=-1;
	if(!tran) no_of_transition=selectMin(no_of_transition,canReach((lane_no xor 1),index,true));
	no_of_transition=selectMinWithTransition(no_of_transition,canReach((lane_no xor 1),index+1));
	no_of_transition=selectMin(no_of_transition,canReach(lane_no,index+1));
	memo[index]=no_of_transition;
	return no_of_transition;
}
void solve(){
	string l1,l2;
	cin>>l1>>l2;
	memo1=*new vector<int>(l1.size(),-1);
	memo2=*new vector<int>(l2.size(),-1);
	lane[0]=l1;
	lane[1]=l2;
	int no_of_transition=-1;
	no_of_transition=selectMin(no_of_transition,canReach(0,0));
	no_of_transition=selectMin(no_of_transition,canReach(1,0));
	if(no_of_transition==-1){
		cout<<"No"<<endl;
	}
	else{
		cout<<"Yes"<<endl;
		cout<<no_of_transition<<endl;
	}
}
signed main(){
	
	ios_base::sync_with_stdio(false);
    cin.tie(NULL);
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("error.txt", "w", stderr);
    freopen("output.txt", "w", stdout);
#endif
	int t=1;
	cin>>t;
	while(t--){
		solve();
	}
	cerr<<"time taken : "<<(float)clock()/CLOCKS_PER_SEC<<" secs"<<endl;
	return 0;
}
