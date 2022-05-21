#include<bits/stdc++.h>
#define int long long
#define double long double
#define space " "
#define endl "\n"
#define pb push_back
#define pii pair<int,int>
#define vi vector<int>
#define vb vector<bool>
#define vc vector<char>
#define vs vector<string>
#define vt vector<T>
#define vpii vector<pii>
#define vvi vector<vi>
#define vvb vector<vb>
#define vvc vector<vc>
#define vvs vector<vs>
#define vvt vector<vt>
#define vvpii vector<vpii>
#define MOD1 1000000007
#define F(a,b,c) for(int (a)=(b);(a)<(c);++(a))
#define FN(a,b,c) for(int (a)=(b);(a)<=(c);++(a))
#define FD(a,b,c) for(int (a)=(b);(a)>(c);--(a))
#define FND(a,b,c) for(int (a)=(b);(a)>=(c);--(a))
#define FSQ(a,b,c) for(int (a)=(b);(a)*(a)<(c);++(a))
#define FNSQ(a,b,c) for(int (a)=(b);(a)*(a)<=(c);++(a))
#define SQR(x) ((int)((x)*(x)))
#define RESET(a,b) memset(a,b,sizeof(a))
#define mp make_pair
#define ALL(v) v.begin(),v.end()
#define ALLA(arr,sz) arr,arr+sz
#define SIZE(v) (int)v.size()
#define SORT(v) sort(ALL(v))
#define REVERSE(v) reverse(ALL(v))
#define SORTA(arr,sz) sort(ALLA(arr,sz))
#define REVERSEA(arr,sz) reverse(ALLA(arr,sz))
#define PERMUTE next_permutation
#define MAXN2 (1e5+10)
#define MAXN1 (1e6+10)
#define INF1 (1e10+10)
#define INF2 (1e12+10)
#define INF3 (1e15+10)
#define INF4 (1e18+10)
#define PI 3.1415926535897932
#define FEACH(a,b) for(auto &(a):(b))
#define TONUM(c) (c-'0')
#define TOCHAR(c) (c+'0')
#define GCD(a,b) (__gcd((a),(b)))
#define LCM(a,b) ((a)*((b)/GCD((a),(b))))
#define ADDM(a,b,mod) (((a)%(mod) + (b)%(mod))%mod)
#define SUBM(a,b,mod) ((((a)%(mod) - (b)%(mod))%mod + mod)%mod)
#define MULM(a,b,mod) (((a)*(b))%mod)
#define YESNO1(b) ((b)?(println("YES")):(println("NO")))
#define YESNO2(b) ((b)?(println("Yes")):(println("No")))
#define YESNO3(b)  ((b)?(println("yes")):(println("no")))
#define MID(a,b) (((a)+(b))/2)
#define LSHIFT(a,b) (((int)(a))<<(b))
#define RSHIFT(a,b) (((int)(a))>>(b))
#define FASTIO ios_base::sync_with_stdio(false);cin.tie(NULL);
using namespace std;
template<typename T>void read(T &a){cin>>a;}
template<typename T>void read(T &a,T &b){cin>>a>>b;}
template<typename T>void read(T &a,T &b,T &c){cin>>a>>b>>c;}
template<typename T>void read(T a[],int n){F(i,0,n) cin>>a[i];}
void print(){cout<<" "<<endl;}
template<typename T>void print(T &a){cout<<a<<" ";}
template<typename T>void print(T &a,T &b){cout<<a<<" "<<b<<" ";}
template<typename T>void print(T &a,T &b,T &c){cout<<a<<" "<<b<<" "<<c<<" ";}
void println(){cout<<endl;}
template<typename T>void println(T &a){cout<<a<<endl;}
template<typename T>void println(T &a,T &b){cout<<a<<" "<<b<<endl;}
template<typename T>void println(T &a,T &b,T &c){cout<<a<<" "<<b<<" "<<c<<endl;}
template<typename T>void println(T a[],int n){F(i,0,n) cout<<a[i]<<" ";cout<<endl;}
string tostr(int a){ostringstream ostr;ostr<<a;return ostr.str();}
int tonum(string &s){stringstream str(s);int num;str>>num;return num;}
template<typename T> void printv(vt & v){ FEACH(a,v) print(a); println();}
inline int getseginf(){return INF4;}
template<typename T>T PERFORM(T a,T b,char op){
	if(op=='+') return a+b;
	else if(op=='m') return max(a,b);
	else if(op=='n') return min(a,b);
	else if(op=='|') return a|b;
	else if(op=='&') return a&b;
	else if(op=='^') return a^b;
	else if(op=='-') return a-b;
	else if(op=='*') return a*b;
	else if(op=='/') return a/b;
	return -1;
}
int IDENTITY(char op){
	if(op=='+' || op=='|' || op=='^' || op=='-' ) return 0;
	else if(op=='m') return 0LL-getseginf();
	else if(op=='n') return getseginf();
	return 1;
}
template<typename T>void buildseg(vt & t, vt & a,int v,int tl,int tr,char op){
	if(tl==tr){
		t[v]=a[tl];
	}else if(tl<tr){
		int tm=MID(tl,tr);
		buildseg(t,a,2*v+1,tl,tm,op);
		buildseg(t,a,2*v+2,tm+1,tr,op);
		t[v]=PERFORM(t[2*v+1],t[2*v+2],op);
	}
}
template<typename T>T getseg(vt & t,int v,int tl,int tr,int l,int r,char op){
	if(l>r) return IDENTITY(op);
	else if(tl==l && r==tr){
		return t[v];
	}
	int tm=MID(tl,tr);
	T left=getseg(t,2*v+1,tl,tm,l,min(r,tm),op);
	T right=getseg(t,2*v+2,tm+1,tr,max(l,tm+1),r,op);
	return PERFORM(left,right,op);
}
template<typename T>void updateseg(vt & t,int v,int tl,int tr,int pos,int new_val,char op){
	if(tl==tr){
		t[v]=new_val;
	}else{
		int tm=MID(tl,tr);
		if(pos<=tm){
			updateseg(t,2*v+1,tl,tm,pos,new_val,op);
		}else{
			updateseg(t,2*v+2,tm+1,tr,pos,new_val,op);
		}
		t[v]=PERFORM(t[2*v+1],t[2*v+2],op);
	}
}
void solve(){
	vi v={1,2,3,4,5};
	vi t(4*SIZE(v),0);
	buildseg(t,v,0,0,SIZE(v)-1,'+');
	int ans;
	updateseg(t,0,0,SIZE(v)-1,4,10,'+');
	ans=getseg(t,0,0,SIZE(v)-1,3,4,'+');
	println(ans);
}
inline bool isTakeTestCase(){
	return false;
}
signed main(){
	FASTIO
	int t=1;
	if(isTakeTestCase()) read(t);
	while(t--) solve();
	return 0;
}	


