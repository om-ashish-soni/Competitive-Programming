#include<bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp> // Common file
#include <ext/pb_ds/tree_policy.hpp> 
#include <ext/pb_ds/detail/standard_policies.hpp>
using namespace __gnu_pbds;
using namespace std;
template<
typename Key, // Key type
typename Mapped, // Mapped-policy
typename Cmp_Fn = std::less<Key>, // Key comparison functor
typename Tag = rb_tree_tag, // Specifies which underlying data structure to use
template<
typename Const_Node_Iterator,
typename Node_Iterator,
typename Cmp_Fn_,
typename Allocator_>
class Node_Update = null_node_update, // A policy for updating node invariants
typename Allocator = std::allocator<char> > // An allocator type
class pbds_tree;
// typedef tree<int,null_type,less<int>,rb_tree_tag,tree_order_statistics_node_update> ordered_set;
template <class T> using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
template <class K, class V> using ordered_map = tree<K, V, less<K>, rb_tree_tag, tree_order_statistics_node_update>;

#define int long long
#define double long double
#define space " "
#define endl "\n"
#define pb push_back
#define pii pair<int,int>
#define pss pair<string,string>
#define pivi pair<int,vector<int>>
#define pipii pair<int, pii>
#define ptt pair<T,T>
#define vi vector<int>
#define vb vector<bool>
#define vc vector<char>
#define vs vector<string>
#define vt vector<T>
#define vpii vector<pii>
#define vpss vector<pss>
#define vptt vector<ptt>
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
#define BOOLALPHA cout<<boolalpha;


template<typename T>void read(T &a){cin>>a;}
template<typename T>void read(T &a,T &b){cin>>a>>b;}
template<typename T>void read(T &a,T &b,T &c){cin>>a>>b>>c;}
template<typename T>void read(T a[],int n){F(i,0,n) cin>>a[i];}
template<typename T>void read(ptt & pr){read(pr.first,pr.second);}
template<typename T>void readv(vt & v){FEACH(a,v) read(a);}
template<typename T>void readm(vvt & v){FEACH(a,v) readv(a);}

void print(){cout<<" "<<endl;}
template<typename T>void print(T &a){cout<<a<<" ";}
template<typename T>void print(T &a,T &b){cout<<a<<" "<<b<<" ";}
template<typename T>void print(T &a,T &b,T &c){cout<<a<<" "<<b<<" "<<c<<" ";}
template<typename T>void print(ptt & pr){cout<<pr.first<<" "<<pr.second<<" ";}
void println(){cout<<endl;}
template<typename T>void println(T &a){cout<<a<<endl;}
template<typename T>void println(T &a,T &b){cout<<a<<" "<<b<<endl;}
template<typename T>void println(T &a,T &b,T &c){cout<<a<<" "<<b<<" "<<c<<endl;}
template<typename T>void println(ptt & pr){cout<<pr.first<<" "<<pr.second<<endl;}
template<typename T>void println(T a[],int n){F(i,0,n) cout<<a[i]<<" ";cout<<endl;}
string tostr(int a){ostringstream ostr;ostr<<a;return ostr.str();}
int tonum(string &s){stringstream str(s);int num;str>>num;return num;}

template<typename T> void printv(vt & v){ FEACH(a,v) print(a); println();}
template<typename T> void printm(vvt & v){ FEACH(a,v) printv(a);}
void printb(bool b){cout<<b<<" ";}
void printb(bool b1,bool b2){printb(b1);printb(b2);}
void printlnb(bool b){printb(b);println();}
void printlnb(bool b1,bool b2){printb(b1);printb(b2);println();}
using namespace std;
void reject(){
    cout<<-1<<endl;
    return;
}
pair<int,int> extended_gcd(int a,int b){
    if(b==0) return{1,1};
    pair<int,int> pr=extended_gcd(b,a%b);
    return {pr.second,pr.first-(a/b)*pr.second};
}
int hcf(int a,int b){
    if(a==0 || b==0) return max(a,b);
    pair<int,int> pr=extended_gcd(a,b);
    return (a*pr.first + b*pr.second);
}
int lcm(int a,int b){
    return (a*b)/(__gcd(a,b));
}
int gcd(int a,int b){
    return __gcd(a,b);
}
int modSub(int a,int b,int mod){
    return ((a%mod - b%mod + mod)%mod);
}
int modMul(int a,int b,int mod){
    return ((a%mod)*(b%mod))%mod;
}
int modAdd(int a,int b,int mod){
    return ((a%mod)+(b%mod))%mod;
}
int modInv(int a,int mod){
    int x,y;
    pair<int,int> pr=extended_gcd(a,mod);
    x=pr.first;
    y=pr.second;
    int g=(a*x + mod*y);
    if(g!=1){
        cerr<<"modular inverse does not exist , gcd != 1"<<endl;
        exit(0);
    }
    // adding m to avoid negative value of x 
    int res=(x%mod + mod)%mod;
    return res;
}
int modDiv(int a,int b,int mod){
    
    a=a%mod;
    int inv=modInv(b,mod);
    int res=(inv*a)%mod;
    return res;
}
bool isalpha(char c){
    int ascii=(c-'a');
    return ascii>=0 && ascii<=25;
}



void printKickStartCase(int t){
    cout<<"Case #"<<t<<": ";
}


class om_ashish_soni{
public:

    om_ashish_soni(){
        init();
    }
    void solve(int t){
        //shree ganeshay namah
        // println("shree ganeshay namah");
        // println("shreepad rajam sharanam prapadhye");
        int n;
        read(n);
        
        // println("shree ganeshay namah");
        // println("shreepad rajam sharanam prapadhye");

    }   
    void init(){
    }
    void drive(){
        int t=1;
        if(isTakeTestCase()) read(t);//testcase
        F(i,1,t+1){
            solve(i);
        }
    }
    inline bool isTakeTestCase(){
        return true;
        // return false;
    }
};

class Account{
public:
    static void printTime(){
        double tm=(float)clock()/CLOCKS_PER_SEC;
        cerr<<"time taken : "<<tm<<endl;
    }
};
signed main(){
    FASTIO;
    BOOLALPHA;
    int t=1;
    om_ashish_soni *oas=new om_ashish_soni();
    oas->drive();
    Account::printTime();
    delete oas;
    return 0;
}   


