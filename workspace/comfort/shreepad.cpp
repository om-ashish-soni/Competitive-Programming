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
#define MATHPI 3.1415926535897932
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
// template<typename T>void readv(vt & v){FEACH(a,v) read(a);}
template<typename T>void readv(vt & v,int start=0){
    // FEACH(a,v) read(a);
    int n=v.size();
    F(i,start,n){
        read(v[i]);
    }
}

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
template<typename T> void send(T item){return println(item);}
template<typename T> void sendref(T &item){return println(item);}

using namespace std;
void reject(){
    cout<<-1<<endl;
    return;
}

namespace ModuloArithmetic{
    pair<long long,long long> extended_gcd(long long a,long long b){
        if(b==0) return{1,1};
        pair<long long,long long> pr=extended_gcd(b,a%b);
        return {pr.second,pr.first-(a/b)*pr.second};
    }
    long long hcf(long long a,long long b){
        if(a==0 || b==0) return max(a,b);
        pair<long long,long long> pr=extended_gcd(a,b);
        return (a*pr.first + b*pr.second);
    }
    long long lcm(long long a,long long b){
        return (a*b)/(__gcd(a,b));
    }
    long long gcd(long long a,long long b){
        return __gcd(a,b);
    }
    long long modSub(long long a,long long b,long long mod){
        return ((a%mod - b%mod + mod)%mod);
    }
    long long modMul(long long a,long long b,long long mod){
        return ((a%mod)*(b%mod))%mod;
    }
    long long modAdd(long long a,long long b,long long mod){
        return ((a%mod)+(b%mod))%mod;
    }
    long long modInv(long long a,long long mod){
        long long x,y;
        pair<long long,long long> pr=extended_gcd(a,mod);
        x=pr.first;
        y=pr.second;
        long long g=(a*x + mod*y);
        if(g!=1){
            cerr<<"modular inverse does not exist , gcd != 1"<<endl;
            exit(0);
        }
        // adding m to avoid negative value of x 
        long long res=(x%mod + mod)%mod;
        return res;
    }
    long long modDiv(long long a,long long b,long long mod){
        a=a%mod;
        // if(a==0) return 0;
        long long inv=modInv(b,mod);
        long long res=(inv*a)%mod;
        return res;
    }
    long long power(long long x, unsigned long long y, long long p) 
    { 
        long long res = 1; 
        x = x % p; // Update x if it is more than or 
        if (x == 0) return 0; // In case x is divisible by p;
        while (y > 0) { 
            if (y & 1) res = modMul(res,x,p); 
            y = y>>1; // y = y/2 
            x=modMul(x,x,p);
        } 
        return res; 
    }
    long long get_primitive_root (long long p) {
        vector<long long> fact;
        long long phi = p-1,  n = phi;
        for (long long i=2; i*i<=n; ++i)
            if (n % i == 0) {
                fact.push_back (i);
                while (n % i == 0)
                    n /= i;
            }
        if (n > 1)
            fact.push_back (n);

        for (long long res=2; res<=p; ++res) {
            bool ok = true;
            for (size_t i=0; i<fact.size() && ok; ++i)
                ok &= power (res, phi / fact[i], p) != 1;
            if (ok)  return res;
        }
        return -1;
    }
    long long get_root_power(long long num){
        vector<long long> powers(63);
        for(long long i=0;i<63;i++){
            powers[i]=(1LL << i);
        }
        for(long long i=62;i>=0;i--){
            if(num%powers[i]==1) return i;
        }
        return -1;
    }
};

namespace LangUtil{
    bool isalpha(char c){
        int ascii=(c-'a');
        return ascii>=0 && ascii<=25;
    }    
    bool isdigit(char c){
        int ascii=(c-'0');
        return 0<=ascii && ascii<=9;
    }
    bool islower(char c){
        return isalpha(c);
    }
    bool isupper(char c){
        int ascii=(c-'A');
        return ascii>=0 && ascii<=25;
    }
    bool isop(char c){
        string s="+-*/%";
        return s.find(c) != string::npos;
    }
    vector<string> split(string s,char delim=' '){
        vector<string> v;
        v.push_back("");
        for(auto c:s){
            if(c==delim){
                v.push_back("");
            }else{
                v.back().push_back(c);    
            }
            
        }
        return v;
    }
    bool isPal(string s){
        string first=s;
        string second=s;
        reverse(second.begin(),second.end());
        return first==second;
    }
};

namespace Transformer{
    inline int ctoa(char c){
        return c-'a';
    }
    inline char atoc(int a){
        return (char)(a+'a');
    }
    int ctoi(char c){
        return c-'0';
    }
    char itoc(int i){
        return i-0+'0';
    }
    char tolower(char c){
        int ascii=(int)(c-'A');
        char c1=(char)(ascii+'a');
        return c1;
    }
    char toupper(char c){
        int ascii=(int)(c-'a');
        char c1=(char)(ascii+'A');
        return c1;
    }
};

class disjointSet{
    vector<int> ump;
    public:
    vector<int>& getUmp(){
        return ump;
    }
    disjointSet(int n){
        ump.assign(n+1,-1);
    }
    int findSet(int u){
        // cout<<"in findSet "<<u<<endl;
        int r=u;
        while(ump[r]>=0){
            r=ump[r];
        }
        while(u!=r){
            int par=ump[u];
            ump[u]=r;
            u=par;
        }
        return r;
    }
    bool setUnion(int u,int v){
        // cout<<"in setUnion "<<u<<" "<<v<<endl;
        int uroot=findSet(u);
        int vroot=findSet(v);
        // cout<<"root : "<<uroot<<" "<<vroot<<endl;
        if(uroot == vroot) return false;
        int uchild=ump[uroot];
        int vchild=ump[vroot];
        int totalChild=uchild+vchild;
        
        if(uchild>vchild){
            ump[uroot]=vroot;
            ump[vroot]=totalChild;
        }else{
            ump[vroot]=uroot;
            ump[uroot]=totalChild;
        }
        return true;
    }
    bool prefered_union(int u,int v){
        int uroot=findSet(u);
        int vroot=findSet(v);
        if(uroot==vroot) return false;
        int uchild=ump[uroot];
        int vchild=ump[vroot];
        int totalChild=uchild+vchild;
        ump[uroot]=vroot;
        ump[vroot]=totalChild;
        return true;
    }
    bool checkOdd(int l,int r){
        for(int i=l;i<=r;i++){
            // cout<<ump[i]<<" ";
            if(ump[i]<0){
                if(abs(ump[i])%2) return false;
            }
        }
        // cout<<endl;
        return true;
    }

    int getChilds(int u){
        int root=findSet(u);
        return abs(ump[root]);
    }
};


class FFT{
    using cd=complex<double>;
    const double mathpi=MATHPI;
    public : 
    int sz=1;
    vector<cd> fa,fb;
    FFT(vector<int> &ma,vector<int> &mb){
        

        this->fa=vector<cd>(ma.begin(),ma.end());
        this->fb=vector<cd>(mb.begin(),mb.end());
        
        
        while(sz<ma.size()+mb.size()){
            sz<<=1;
        }
        fa.resize(sz);
        fb.resize(sz);


    }
    void fft(vector<cd> & a,bool invert){
        int n=a.size();
        if(n==1) return;
        vector<cd> a0(n/2),a1(n/2);
        for(int i=0;2*i<n;i++){
            a0[i]=a[2*i];
            a1[i]=a[2*i+1];
        }
        fft(a0,invert);
        fft(a1,invert);
        int sign=(invert)?(-1):(1);
        double ang=2*mathpi/n*sign;
        cd omega(1),mult(cos(ang),sin(ang));

        for(int i=0;2*i<n;i++){
            a[i]=a0[i]+omega*a1[i];
            a[i+n/2]=a0[i]-omega*a1[i];
            if(invert){
                a[i]/=2;
                a[i+n/2]/=2;
            }
            omega*=mult;
        }
        
    }
    vector<int> multiply(){
        fft(fa,false);
        fft(fb,false);
        for(int i=0;i<sz;i++){
            fa[i]*=fb[i];
        }
        fft(fa,true);
        vector<int> result(sz);
        for(int i=0;i<sz;i++){
            result[i]=round(fa[i].real());
        }
        return result;
    }
    static void how_to_use(){
        vector<int> a={1,2};
        vector<int> b={2,4,6};
        FFT *fft=new FFT(a,b);
        vector<int> c=fft->multiply();
        for(auto num:c) cout<<num<<" ";cout<<endl;
    }
};
class Graph{
public:
    static void make_tree(vvi & graph,vvi & tree,vi & par,int start,int parent=-1){
        par[start]=parent;
        FEACH(node,graph[start]){
            if(node != parent){
                tree[start].pb(node);
                make_tree(graph,tree,par,node,start);
            }
        }
    }
};
class Sieve{
public:
    vector<int> primes;
    
    vector<int> lp;
    int n=1e5+10;
    Sieve(){
        init();
    }
    Sieve(int n){
        this->n=n;
        init();
    }
    void init(){
        vector<bool> isprm(n,true);
        lp.assign(n,-1);
        
        isprm[0]=isprm[1]=false;
        for(int i=2;i<n;i++){
            if(isprm[i]==false) continue;
            lp[i]=i;
            primes.push_back(i);
            
            for(int j=i+i;j<n;j+=i){
                isprm[j]=false;
                if(lp[j]==-1){
                    lp[j]=i;
                }
                
            }
        }
    }
    vector<int> & get(){
        return primes;
    }
    int getLP(int num){
        return this->lp[num];
    }
    bool isPrime(int num){
        return (lp[num]==num);
    }
    vector<int> getFactors(int num){
        
        set<int> factors;
        while(num>1){
            factors.insert(lp[num]);
            num/=lp[num];
        }
        vector<int> facts;
        for(auto & prm:factors) facts.push_back(prm);
        return facts;
    }
    void print(){
        for(auto &prm:primes) cout<<prm<<" ";cout<<endl;
    }
    static void how_to_use(){
        int limit=1e5+10;
        Sieve *sv=new Sieve(limit);
        vector<int> factors=sv->getFactors(100);
        for(auto fact:factors) cout<<fact<<" ";cout<<endl;
        //logs : 2 5
    }
};
class LazySegmentTree{
    int n=0;
    int MYSIZE=0;
    vector<long long> tree,lazy;
    vector<long long> arr;
    public:
    void init(int n){
        this->n=n;
        this->MYSIZE=4*n+10;
        tree.assign(MYSIZE,0LL);
        lazy.assign(MYSIZE,0LL);
        arr.assign(MYSIZE,0LL);
    }
    void post_init(){
        this->constructST();
    }
    LazySegmentTree(vector<int> & v){
        int n=v.size();
        init(n);
        for(int i=0;i<n;i++){
            arr[i]=v[i];
        }
        post_init();
    }
    LazySegmentTree(int v[],int n){
        init(n);
        for(int i=0;i<n;i++){
            arr[i]=v[i];
        }
        post_init();
    }
    LazySegmentTree(int n){
        init(n);
        post_init();
    }
    void updateRangeUtil(int si, int ss, int se, int us,
                         int ue, int diff)
    {
        if (lazy[si] != 0)
        {
            tree[si] += (se-ss+1)*lazy[si];
            if (ss != se)
            {
                lazy[si*2 + 1]   += lazy[si];
                lazy[si*2 + 2]   += lazy[si];
            }
            lazy[si] = 0;
        }
        if (ss>se || ss>ue || se<us)
            return ;
        if (ss>=us && se<=ue)
        {
            tree[si] += (se-ss+1)*diff;
            if (ss != se)
            {
                lazy[si*2 + 1]   += diff;
                lazy[si*2 + 2]   += diff;
            }
            return;
        }
        int mid = (ss+se)/2;
        updateRangeUtil(si*2+1, ss, mid, us, ue, diff);
        updateRangeUtil(si*2+2, mid+1, se, us, ue, diff);
        tree[si] = tree[si*2+1] + tree[si*2+2];
    }
    void updateRange(int us, int ue, int diff)
    {
       updateRangeUtil(0, 0, n-1, us, ue, diff);
    }
    void update(int us,int ue,int diff){
        updateRange(us,ue,diff);
    }
    // void setupdate(int us,int ue,int value){
    //     int before=query(us,ue);
    //     int delta=value-before;
    //     update(us,ue,delta);
    // }
    int getSumUtil(int ss, int se, int qs, int qe, int si)
    {
        if (lazy[si] != 0)
        {
            tree[si] += (se-ss+1)*lazy[si];
            if (ss != se)
            {
                lazy[si*2+1] += lazy[si];
                lazy[si*2+2] += lazy[si];
            }
            lazy[si] = 0;
        }
        if (ss>se || ss>qe || se<qs)
            return 0;
        if (ss>=qs && se<=qe)
            return tree[si];
        int mid = (ss + se)/2;
        return getSumUtil(ss, mid, qs, qe, 2*si+1) +
               getSumUtil(mid+1, se, qs, qe, 2*si+2);
    }
    int getSum(int qs, int qe)
    {
        if (qs < 0 || qe > n-1 || qs > qe)
        {
            printf("Invalid Input");
            return -1;
        }
        return getSumUtil(0, n-1, qs, qe, 0);
    }
    int query(int qs,int qe){
        return getSum(qs,qe);
    }
    void constructSTUtil(int ss, int se, int si)
    {
        if (ss > se)
            return ;
        if (ss == se){
            tree[si] = arr[ss];
            return;
        }
        int mid = (ss + se)/2;
        if(ss<=mid) constructSTUtil(ss, mid, si*2+1);
        if(mid+1<=se) constructSTUtil(mid+1, se, si*2+2);
        tree[si] = tree[si*2 + 1] + tree[si*2 + 2];
    }
    void constructST(){
        constructSTUtil(0, n-1, 0);
    }
};
class SetLazySegmentTree{
    int n=0;
    int MYSIZE=0;
    vector<long long> tree,lazy,stamp;
    vector<bool> pending;
    vector<long long> arr;
    int tm=0;
    public:
    void init(int n){
        this->n=n;
        this->MYSIZE=4*n+10;
        tree.assign(MYSIZE,0LL);
        lazy.assign(MYSIZE,0LL);
        arr.assign(MYSIZE,0LL);
        stamp.assign(MYSIZE,0LL);
        pending.assign(MYSIZE,false);
        // lazy_stamp.assign(MYSIZE,0LL);
    }
    void post_init(){
        this->constructST();
    }
    SetLazySegmentTree(vector<int> & v){
        int n=v.size();
        init(n);
        for(int i=0;i<n;i++){
            arr[i]=v[i];
        }
        post_init();
    }
    SetLazySegmentTree(int v[],int n){
        init(n);
        for(int i=0;i<n;i++){
            arr[i]=v[i];
        }
        post_init();
    }
    SetLazySegmentTree(int n){
        init(n);
        post_init();
    }
    void updateRangeUtil(int si, int ss, int se, int us,
                         int ue, int diff,int stamp_value)
    {
        
        // if (lazy[si] != 0)
        if (pending[si])
        {
            tree[si] = (se-ss+1)*lazy[si];
            if (ss != se)
            {

                if(stamp[si*2+1]<=stamp[si]){
                    lazy[si*2 + 1]   = lazy[si];
                    stamp[si*2 + 1]   = stamp[si];
                    pending[si*2+1]=true;
                    // cout<<"stamp of "<<si*2+1<<" "<<" is "<<stamp[si]<<endl;
                }
                
                if(stamp[si*2+2]<=stamp[si]){
                    lazy[si*2 + 2]   = lazy[si];    
                    stamp[si*2 + 2]   = stamp[si];
                    pending[si*2+2]=true;
                    // cout<<"stamp of "<<si*2+2<<" "<<" is "<<stamp[si]<<endl;
                }

            }
            pending[si]=false;
            // lazy[si] = 0;
        }
        if (ss>se || ss>ue || se<us)
            return ;

        

        if (ss>=us && se<=ue)
        {
            tree[si] = (se-ss+1)*diff;
            if (ss != se)
            {
                // lazy[si*2 + 1] = diff;
                // lazy[si*2 + 2] = diff;

                if(stamp[si*2+1]<=stamp_value){
                    lazy[si*2 + 1]   = diff;
                    stamp[si*2 + 1]   = stamp_value;
                    pending[si*2+1]=true;
                    // cout<<"stamp of "<<si*2+1<<" "<<" is "<<stamp_value<<" lazy : "<<lazy[si*2+1]<<endl;
                }
                
                if(stamp[si*2+2]<=stamp_value){
                    lazy[si*2 + 2]   = diff;    
                    stamp[si*2 + 2]   = stamp_value;
                    pending[si*2+2]=true;
                    // cout<<"stamp of "<<si*2+2<<" "<<" is "<<stamp_value<<" lazy : "<<lazy[si*2+1]<<endl;
                }

            }
            stamp[si]=stamp_value;
            return;
        }
        int mid = (ss+se)/2;
        updateRangeUtil(si*2+1, ss, mid, us, ue, diff,stamp_value);
        updateRangeUtil(si*2+2, mid+1, se, us, ue, diff,stamp_value);
        tree[si] = tree[si*2+1] + tree[si*2+2];
        // tree[si] = query(si*2+1,si*2+1) + query(si*2+2,si*2+2);
    }
    void updateRange(int us, int ue, int diff)
    {
       ++tm;
       updateRangeUtil(0, 0, n-1, us, ue, diff,tm);
    }
    void update(int us,int ue,int diff){
        updateRange(us,ue,diff);
    }
    // void setupdate(int us,int ue,int value){
    //     int before=query(us,ue);
    //     int delta=value-before;
    //     update(us,ue,delta);
    // }
    int getSumUtil(int ss, int se, int qs, int qe, int si)
    {
        // cout<<"in query : "<<ss<<" , "<<se<<" at si : "<<si<<" lazy : "<<lazy[si]<<endl;
        if (pending[si])
        {

            tree[si] = (se-ss+1)*lazy[si];
            if (ss != se)
            {
                if(stamp[si*2+1]<=stamp[si]){
                    lazy[si*2+1] = lazy[si];
                    stamp[si*2+1]=stamp[si]; 
                    pending[si*2+1]=true;   
                }
                if(stamp[si*2+2]<=stamp[si]){
                    lazy[si*2+2] = lazy[si];
                    stamp[si*2+2]=stamp[si];    
                    pending[si*2+2]=true;
                }
            }
            // lazy[si] = 0;
            pending[si]=false;
        }
        if (ss>se || ss>qe || se<qs)
            return 0;
        if (ss>=qs && se<=qe)
            return tree[si];
        int mid = (ss + se)/2;
        return getSumUtil(ss, mid, qs, qe, 2*si+1) +
               getSumUtil(mid+1, se, qs, qe, 2*si+2);
    }
    int getSum(int qs, int qe)
    {
        if (qs < 0 || qe > n-1 || qs > qe)
        {
            printf("Invalid Input");
            return -1;
        }
        return getSumUtil(0, n-1, qs, qe, 0);
    }
    int query(int qs,int qe){
        return getSum(qs,qe);
    }
    void constructSTUtil(int ss, int se, int si)
    {
        if (ss > se)
            return ;
        if (ss == se){
            tree[si] = arr[ss];
            return;
        }
        int mid = (ss + se)/2;
        if(ss<=mid) constructSTUtil(ss, mid, si*2+1);
        if(mid+1<=se) constructSTUtil(mid+1, se, si*2+2);
        tree[si] = tree[si*2 + 1] + tree[si*2 + 2];
    }
    void constructST(){
        constructSTUtil(0, n-1, 0);
    }
    static void how_to_use(){
        vector<int> arr={1,2,3,4};
        SetLazySegmentTree *mylst=new SetLazySegmentTree(arr);
        mylst->update(0,3,0);
        mylst->update(2,3,2);
        mylst->update(0,2,10);
        int ans=mylst->query(1,2);
        cout<<ans<<endl;
    }
};
class ShiftHashLazySegmentTree{
    int n=0;
    int MYSIZE=0;
    vector<map<int,int>> tree,lazy;
    vector<deque<int>> tree_dq;
    vector<long long> arr;
    public:
    void init(int n){
        this->n=n;
        this->MYSIZE=4*n+10;
        tree.resize(MYSIZE);
        lazy.resize(MYSIZE);
        arr.assign(MYSIZE,0);
    }
    void post_init(){
        this->constructST();
    }
    ShiftHashLazySegmentTree(vector<int> & v){
        int n=v.size();
        init(n);
        for(int i=0;i<n;i++){
            arr[i]=v[i];
        }
        post_init();
    }
    ShiftHashLazySegmentTree(int v[],int n){
        init(n);
        for(int i=0;i<n;i++){
            arr[i]=v[i];
        }
        post_init();
    }
    ShiftHashLazySegmentTree(int n){
        init(n);
        post_init();
    }
    // void updateRangeUtil(int si, int ss, int se, int us,
    //                      int ue, int diff)
    // {
    //     if (lazy[si] != 0)
    //     {
    //         tree[si] += (se-ss+1)*lazy[si];
    //         if (ss != se)
    //         {
    //             lazy[si*2 + 1]   += lazy[si];
    //             lazy[si*2 + 2]   += lazy[si];
    //         }
    //         lazy[si] = 0;
    //     }
    //     if (ss>se || ss>ue || se<us)
    //         return ;
    //     if (ss>=us && se<=ue)
    //     {
    //         tree[si] += (se-ss+1)*diff;
    //         if (ss != se)
    //         {
    //             lazy[si*2 + 1]   += diff;
    //             lazy[si*2 + 2]   += diff;
    //         }
    //         return;
    //     }
    //     int mid = (ss+se)/2;
    //     updateRangeUtil(si*2+1, ss, mid, us, ue, diff);
    //     updateRangeUtil(si*2+2, mid+1, se, us, ue, diff);
    //     tree[si] = tree[si*2+1] + tree[si*2+2];
    // }
    // void updateRange(int us, int ue, int diff)
    // {
    //    updateRangeUtil(0, 0, n-1, us, ue, diff);
    // }
    // void update(int us,int ue,int diff){
    //     updateRange(us,ue,diff);
    // }
    // // void setupdate(int us,int ue,int value){
    // //     int before=query(us,ue);
    // //     int delta=value-before;
    // //     update(us,ue,delta);
    // // }
    // int getSumUtil(int ss, int se, int qs, int qe, int si)
    // {
    //     if (lazy[si] != 0)
    //     {
    //         tree[si] += (se-ss+1)*lazy[si];
    //         if (ss != se)
    //         {
    //             lazy[si*2+1] += lazy[si];
    //             lazy[si*2+2] += lazy[si];
    //         }
    //         lazy[si] = 0;
    //     }
    //     if (ss>se || ss>qe || se<qs)
    //         return 0;
    //     if (ss>=qs && se<=qe)
    //         return tree[si];
    //     int mid = (ss + se)/2;
    //     return getSumUtil(ss, mid, qs, qe, 2*si+1) +
    //            getSumUtil(mid+1, se, qs, qe, 2*si+2);
    // }
    // int getSum(int qs, int qe)
    // {
    //     if (qs < 0 || qe > n-1 || qs > qe)
    //     {
    //         printf("Invalid Input");
    //         return -1;
    //     }
    //     return getSumUtil(0, n-1, qs, qe, 0);
    // }
    // int query(int qs,int qe){
    //     return getSum(qs,qe);
    // }
    void constructSTUtil(int ss, int se, int si)
    {
        if (ss > se)
            return ;
        if (ss == se){
            tree[si][arr[ss]]++;
            tree_dq[si].push_back(arr[ss]);
            return;
        }
        int mid = (ss + se)/2;
        if(ss<=mid) constructSTUtil(ss, mid, si*2+1);
        if(mid+1<=se) constructSTUtil(mid+1, se, si*2+2);
        merge(tree[si*2 + 1] , tree[si*2 + 2] , tree[si]) ;
        merge(tree_dq[si*2+1],tree_dq[si*2+2],tree_dq[si]);
    }
    void constructST(){
        constructSTUtil(0, n-1, 0);
    }
    static void merge(map<int, int> & mp1,map<int, int> & mp2,map<int, int> & mp){
        for(auto & pr:mp1){
            mp[pr.first]+=pr.second;
        }
        for(auto & pr:mp2){
            mp[pr.first]+=pr.second;
        }
    }
    static void merge(deque<int> & dq1,deque<int> & dq2,deque<int> & dq){
        for(auto num:dq1){
            dq.push_back(num);
        }
        for(auto num:dq2){
            dq.push_back(num);
        }
    }
    static void test(){
        // map<int,int> mp1= { { 2, 3}, { 1, 4}, {8,5}};
        // map<int,int> mp2= { { 2, 1}, {1, 7}, {8,4}};
        // map<int,int> mp;
        // merge(mp1,mp2,mp);
        // FEACH(pr,mp){
        //     cout<<pr.first<<" , "<<pr.second<<endl;
        // }
        // deque<int> dq1={1,2,3};
        // deque<int> dq2={4,5,6};
        // deque<int> dq;
        // merge(dq1,dq2,dq);
        // for(auto num:dq){
        //     cout<<num<<" ";
        // }
        // cout<<endl;
    }
};
class MaxLazySegmentTree{
    int n=0;
    int MYSIZE=0;
    vector<long long> tree,lazy;
    vector<long long> arr;
    public:
    void init(int n){
        this->n=n;
        this->MYSIZE=4*n+10;
        tree.assign(MYSIZE,0LL);
        lazy.assign(MYSIZE,0LL);
        arr.assign(MYSIZE,0LL);
    }
    void post_init(){
        this->constructST();
    }
    MaxLazySegmentTree(vector<int> & v){
        int n=v.size();
        init(n);
        for(int i=0;i<n;i++){
            arr[i]=v[i];
        }
        post_init();
    }
    MaxLazySegmentTree(int v[],int n){
        init(n);
        for(int i=0;i<n;i++){
            arr[i]=v[i];
        }
        post_init();
    }
    MaxLazySegmentTree(int n){
        init(n);
        post_init();
    }
    void updateRangeUtil(int si, int ss, int se, int us,
                         int ue, int diff)
    {
        if (lazy[si] != 0)
        {
            tree[si] += lazy[si];
            if (ss != se)
            {
                lazy[si*2 + 1]   += lazy[si];
                lazy[si*2 + 2]   += lazy[si];
            }
            lazy[si] = 0;
        }
        if (ss>se || ss>ue || se<us)
            return ;
        if (ss>=us && se<=ue)
        {
            tree[si] += diff;
            if (ss != se)
            {
                lazy[si*2 + 1]   += diff;
                lazy[si*2 + 2]   += diff;
            }
            return;
        }
        int mid = (ss+se)/2;
        updateRangeUtil(si*2+1, ss, mid, us, ue, diff);
        updateRangeUtil(si*2+2, mid+1, se, us, ue, diff);
        tree[si] = max(tree[si*2+1] , tree[si*2+2]);
    }
    void updateRange(int us, int ue, int diff)
    {
       updateRangeUtil(0, 0, n-1, us, ue, diff);
    }
    void update(int us,int ue,int diff){
        updateRange(us,ue,diff);
    }
      
    int getMaxUtil(int ss, int se, int qs, int qe, int si)
    {
        if (lazy[si] != 0)
        {
            tree[si] += lazy[si];
            if (ss != se)
            {
                lazy[si*2+1] += lazy[si];
                lazy[si*2+2] += lazy[si];
            }
            lazy[si] = 0;
        }
        if (ss>se || ss>qe || se<qs)
            return 0;
        if (ss>=qs && se<=qe)
            return tree[si];
        int mid = (ss + se)/2;
        return max(getMaxUtil(ss, mid, qs, qe, 2*si+1) ,
               getMaxUtil(mid+1, se, qs, qe, 2*si+2));
    }
    int getMax(int qs, int qe)
    {
        if (qs < 0 || qe > n-1 || qs > qe)
        {
            printf("Invalid Input");
            return -1;
        }
        return getMaxUtil(0, n-1, qs, qe, 0);
    }
    void constructSTUtil(int ss, int se, int si)
    {
        if (ss > se)
            return ;
        if (ss == se){
            tree[si] = arr[ss];
            return;
        }
        int mid = (ss + se)/2;
        if(ss<=mid) constructSTUtil(ss, mid, si*2+1);
        if(mid+1<=se) constructSTUtil(mid+1, se, si*2+2);
        tree[si] = max(tree[si*2 + 1] , tree[si*2 + 2]);
    }
    void constructST(){
        constructSTUtil(0, n-1, 0);
    }
};
class LazySumXorSegmentTree{
    int n=0;
    int MYSIZE=0;
    vector<long long> tree;
    vector<bool> lazy;
    vector<long long> arr;
    public:
    void init(int n){
        this->n=n;
        this->MYSIZE=4*n+10;
        tree.assign(MYSIZE,0LL);
        lazy.assign(MYSIZE,false);
        arr.assign(MYSIZE,0LL);
    }
    void post_init(){
        this->constructST();
    }
    LazySumXorSegmentTree(vector<int> & v){
        int n=v.size();
        init(n);
        for(int i=0;i<n;i++){
            arr[i]=v[i];
        }
        post_init();
    }
    LazySumXorSegmentTree(int v[],int n){
        init(n);
        for(int i=0;i<n;i++){
            arr[i]=v[i];
        }
        post_init();
    }
    LazySumXorSegmentTree(int n){
        init(n);
        post_init();
    }
    void updateRangeUtil(int si, int ss, int se, int us,
                         int ue, int diff)
    {
        if (lazy[si])
        {
            tree[si] = ((se-ss+1)-tree[si]);
            if (ss != se)
            {
                lazy[si*2 + 1]   = !lazy[si*2 + 1];
                lazy[si*2 + 2]   = !lazy[si*2 + 2];
            }
            lazy[si] = false;
        }
        if (ss>se || ss>ue || se<us)
            return ;
        if (ss>=us && se<=ue)
        {
            tree[si] = ((se-ss+1)-tree[si]);
            if (ss != se)
            {
                lazy[si*2 + 1]   = !lazy[si*2 + 1];
                lazy[si*2 + 2]   = !lazy[si*2 + 2];
            }
            return;
        }
        int mid = (ss+se)/2;
        updateRangeUtil(si*2+1, ss, mid, us, ue, diff);
        updateRangeUtil(si*2+2, mid+1, se, us, ue, diff);
        tree[si] = tree[si*2+1] + tree[si*2+2];
    }
    void updateRange(int us, int ue, int diff)
    {
       updateRangeUtil(0, 0, n-1, us, ue, diff);
    }
    void update(int us,int ue,int diff){
        updateRange(us,ue,diff);
    }
    int getSumUtil(int ss, int se, int qs, int qe, int si)
    {
        if (lazy[si])
        {
            tree[si] = ((se-ss+1)-tree[si]);
            if (ss != se)
            {
                lazy[si*2 + 1]   = !lazy[si*2 + 1];
                lazy[si*2 + 2]   = !lazy[si*2 + 2];
            }
            lazy[si] = false;
        }
        if (ss>se || ss>qe || se<qs)
            return 0;
        if (ss>=qs && se<=qe)
            return tree[si];
        int mid = (ss + se)/2;
        return getSumUtil(ss, mid, qs, qe, 2*si+1) +
               getSumUtil(mid+1, se, qs, qe, 2*si+2);
    }
    int getSum(int qs, int qe)
    {
        if (qs < 0 || qe > n-1 || qs > qe)
        {
            printf("Invalid Input");
            return -1;
        }
        return getSumUtil(0, n-1, qs, qe, 0);
    }
    int query(int qs,int qe){
        return getSum(qs,qe);
    }
    void constructSTUtil(int ss, int se, int si)
    {
        if (ss > se)
            return ;
        if (ss == se){
            tree[si] = arr[ss];
            return;
        }
        int mid = (ss + se)/2;
        if(ss<=mid) constructSTUtil(ss, mid, si*2+1);
        if(mid+1<=se) constructSTUtil(mid+1, se, si*2+2);
        tree[si] = tree[si*2 + 1] + tree[si*2 + 2];
    }
    void constructST(){
        constructSTUtil(0, n-1, 0);
    }

    static void how_to_use(){
        vector<int> bits={1,1,0,1,1};
        LazySumXorSegmentTree *lsxt=new LazySumXorSegmentTree(bits);
        lsxt->update(1,2,1);
        int ans=lsxt->query(2,2);
        cout<<ans<<endl;
        delete lsxt;
    }
};

// fenwick tree
class fenwickTree{
    vector<int> BIT;
    int n;
    public : 
    fenwickTree(int n){
        this->n=n;
        // BIT=*new vector<int>(n,0);
        BIT.assign(n,0);
    }
    fenwickTree(int *arr,int n){
        
        this->n=n;
        BIT=*new vector<int>(n,0);
        BIT[0]=arr[0];
        for(int i=1;i<n;i++){
            this->update(i,arr[i]);
        }
    }
    fenwickTree(vector<int>&v){
        this->n=v.size();
        BIT=*new vector<int>(n,0);
        BIT[0]=v[0];
        for(int i=1;i<n;i++){
            this->update(i,v[i]);
        }
    }
    void update(int index, int delta)
    {
          if(index==0) {BIT[index]+=delta;return;}
          for(; index < n; index += index&-index)

            BIT[index] += delta;
    }
    int get(int index)
    {
         int sum = BIT[0];
         for(; index > 0; index -= index&-index)
            sum += BIT[index];
         return sum;
    }
    void print(){
        for(int i=0;i<n;i++){
            cout<<BIT[i]<<" ";
        }
        cout<<endl;
    }
    int size(){
        return this->n;
    }
};

class KMP{
public:
    string s;
    int n;
    vector<int> lps;
    KMP(string s){
        this->s=s;
        this->n=this->s.size();
        this->lps.assign(n,0);
        buildLPS();
    }
    void buildLPS(){
        for(int i=1;i<n;i++){
            int j=lps[i-1];
            while(j>0 && s[i] != s[j]){
                j=lps[j-1];
            }
            if(s[i]==s[j]) j++;
            // cout<<"i : "<<i<<" , s[i] : "<<s[i]<<" , j : "<<j<<endl;
            lps[i]=j;
        }
    }
    vector<int> getLPS(){
        return lps;
    }
    vector<int> findIn(string & text){
        vector<int> founds;
        int k=0;
        int textsize=text.size();
        for(int i=0;i<textsize;i++){
            while(k>0 && text[i] != s[k]){
                k=this->lps[k-1];                
            }
            if(text[i]==s[k]){
                k++;
            }
            if(k==n){
                
                int index=i-n+1;
                // cout<<"found at : "<<index<<endl;
                k=this->lps[k-1];
                founds.push_back(index);
            }
        }
        return founds;
    }
    static vector<int> find(string & text,string & pattern){
        KMP *kmp=new KMP(pattern);
        vector<int> founds=kmp->findIn(text);
        delete kmp;
        return founds;
    }
    static void how_to_use(){
        string text="ABABDABACDABABCABAB";
        string pattern="ABABCABAB";
        vector<int> founds=KMP::find(text,pattern);
        int index=-1;
        if(founds.size()==0){
            index=-1;
            cout<<index<<endl;
        }else{
            int firstIndex=founds.front();
            int lastIndex=founds.back();
            cout<<firstIndex<<" , "<<lastIndex<<endl;
        }
    }
};


using namespace ModuloArithmetic;

using namespace Transformer;
class NTT {
public:
    
    vector<int> a;
    int n;
    bool invert=false;
    int root=5;
    int root_inv=4404020;
    int root_power=20;
    int mod=7340033;
    NTT(vector<int> & a,int mod=7340033,bool invert=false){

        this->invert=invert;
        assign(a);
        root_calculation();
        bitreverse();
        process();
        
    }
    void assign(vector<int> & a){
        this->n=a.size();
        int l2=ceil(log2(n));
        this->n=(1LL<<l2);
        this->a.assign(n,0LL);
        for(int i=0;i<a.size();i++){
            this->a[i]=a[i];
        }
    }
    void root_calculation(){
        this->root_power=get_root_power(mod);
        if(this->root_power == -1){
            cerr<<" root_power does not exist, please enter valid mod prime number"<<endl;
            cout<<" root_power does not exist, please enter valid mod prime number"<<endl;
            exit(0);
        }
        // cout<<"root_power : "<<root_power<<endl;
        this->root=get_primitive_root(mod);
        this->root_inv=modInv(this->root,mod);

        // cout<<"root : "<<root<<endl;
        // cout<<"root_inv : "<<root_inv<<endl;
    }
    void bitreverse(){
        for (int i = 1, j = 0; i < n; i++) {
            int bit = n >> 1;
            for (; j & bit; bit >>= 1)
                j ^= bit;
            j ^= bit;

            if (i < j)
                swap(a[i], a[j]);
        }
    }
    void process(){
        for (int len = 2; len <= n; len <<= 1) {
            int wlen = invert ? root_inv : root;
            for (int i = len; i < root_power; i <<= 1)
                wlen = (int)(1LL * wlen * wlen % mod);

            for (int i = 0; i < n; i += len) {
                int w = 1;
                for (int j = 0; j < len / 2; j++) {
                    int u = a[i+j], v = (int)(1LL * a[i+j+len/2] * w % mod);
                    a[i+j] = u + v < mod ? u + v : u + v - mod;
                    a[i+j+len/2] = u - v >= 0 ? u - v : u - v + mod;
                    w = (int)(1LL * w * wlen % mod);
                }
            }
        }

        if (invert) {
            int n_1 = modInv(n, mod);
            for (int & x : a)
                x = (int)(1LL * x * n_1 % mod);
        }
    }
    vector<int> get(){
        return this->a;
    }

};
class NTTMultiply{
    vector<int> result;
    int mod;
public:
    NTTMultiply(vector<int> & fa,vector<int>& fb,int mod){
        this->mod=mod;
        multiply(fa,fb);
    }
    vector<int> get(){
        return this->result;
    }
    void multiply(vector<int> & fa,vector<int> & fb){
        NTT *nt1=new NTT(fa,mod);
        NTT *nt2=new NTT(fb,mod);
        int sz=max(fa.size(),fb.size());
        int l2=ceil(log2(sz));
        sz=(1LL<<l2);
        for(int i=fa.size();i<sz;i++){
            fa.push_back(0);
        }
        for(int i=fb.size();i<sz;i++){
            fb.push_back(0);
        }
        vector<int> vfa=nt1->get();
        vector<int> vfb=nt2->get();

        // cout<<vfa.size()<<" "<<vfb.size()<<endl;
        for(int i=0;i<sz;i++){
            vfa[i]=modMul(vfa[i],vfb[i],mod);
        }
        
        NTT *nt3=new NTT(vfa,mod,true);
        this->result=nt3->get();
    }
    static void how_to_use(){
        vector<int> a={1,2};
        vector<int> b={2,4,6};
        FFT *fft=new FFT(a,b);
        vector<int> c=fft->multiply();
        for(auto num:c) cout<<num<<" ";cout<<endl;
    }
};
string encode(vi & v,int limit){
    string s;
    int n=v.size();
    F(i,0,n) s.push_back('*');
    for(int i=0;i<=limit;i++){
        int index=v[i];
        s[index]=(char)(i+'0');
    }
    return s;
}
void flip(string & s,int limit){
    F(i,0,limit){
        s[i]=(s[i] ^ 1);
    }
}
int cast(char c){
    if(c=='0') return 0;
    if(c=='1') return 1;
    if(c=='?') return 2;
    return -1;
}
bool check_border(int i,int j,int n,int m){
    return i>=0 && j>=0 && i<n && j<m;
}
int get_linear_index(int i,int j,int m){
    return i*m+j;
}

int kadene(vi & v){
    int n=v.size();
    int mx_so_far=0;
    int mx=0;
    FEACH(num,v){
        mx_so_far=max(mx_so_far,0LL);
        mx_so_far+=num;
        mx=max(mx,mx_so_far);
    }
    return mx;
}


class NCRefficient{
    public : 
    int n,mod,r;
    vector<int> fact,invFact,invNum;
    void calculateFactorial(){
        fact[0]=fact[1]=1;
        for(int i=2;i<=n;i++){
            fact[i]=(fact[i-1]*i)%mod;
        }
        return;
    }
    void calculateInverseNum(){
        invNum[0]=invNum[1]=1;
        for(int i=2;i<=n;i++){
            invNum[i]=invNum[mod % i]*(mod - mod/i)%mod;
        }
    }
    void calculateInverseFactorial(){
        invFact[0]=invFact[1]=1;
        for(int i=2;i<=n;i++){
            invFact[i]=(invNum[i]*invFact[i-1])%mod;
        }       
    }
    NCRefficient(int n,int mod):n(n),mod(mod){
        fact.resize(n+1);
        invFact.resize(n+1);
        invNum.resize(n+1);
        this->calculateFactorial();
        this->calculateInverseNum();
        this->calculateInverseFactorial();
    }
    int get(int N,int r){
        if(N>n) return 0;
        if(r<0 || r>N) return 0;
        int ans=(fact[N]*invFact[r])%mod *(invFact[N-r])%mod;
        return ans;
    }
};
class MergeSort{
public:
    vector<int> v;
    vector<pii> inversions;
    MergeSort(vi & arr){
        this->v=arr;
        int n=this->v.size();
        mgsort(0,n-1);
    }
    void mgsort(int l,int r){
        int sz=r-l+1;
        // cout<<l<<" "<<r<<endl;

        if(sz<2) return;
        if(sz==2){
            if(v[l]>v[l+1]){
                inversions.push_back({l,l+1});
                swap(v[l],v[l+1]);
                return;
            }
            return;
        }
        int mid=(l+r)/2;
        mgsort(l,mid);
        mgsort(mid+1,r);
        int left=l;
        int right=mid+1;
        int offset=mid-left+1;
        if(v[left]>v[right]){
            F(i,left,mid+1){
                inversions.push_back({i,i+offset});
                swap(v[i],v[i+offset]);
            }
        }
    }
    vector<int> get_sorted(){
        return this->v;
    }
    vector<pair<int,int>> get_inversions(){
        return this->inversions;
    }

};


using namespace LangUtil;   
namespace Solution{
    namespace MergeSortTree {
    //BST with extra functions https://c...content-available-to-author-only...s.com/blog/entry/11080
    //order_of_key - # of elements *strictly* less than given element
    //find_by_order - find kth largest element, k is 0 based so find_by_order(0) returns min element
    template<class T> using indexed_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
    //example initialization:
    indexed_set<pair<long long, int>> is;
    //hash table (apparently faster than unordered_map): https://c...content-available-to-author-only...s.com/blog/entry/60737
    //example initialization:
    gp_hash_table<string, long long> ht;
     
     
    //For point updates: either switch to policy based BST, or use sqrt decomposition
    struct merge_sort_tree {
        const int N;
        vector<int> arr;
        vector<indexed_set<pair<int,int>>> tree;
        merge_sort_tree(const vector<int>& a_arr) : N(a_arr.size()), arr(a_arr), tree(2 * N) {
            for (int i = 0, j = 1 << __lg(2 * N - 1); i < N; i++, j = (j + 1) % N + N)
                tree[j].insert({arr[i], i});
            for (int i = N - 1; i >= 1; i--) {
                for(pair<int,int> e : tree[2 * i]) tree[i].insert(e);
                for(pair<int,int> e : tree[2 * i + 1]) tree[i].insert(e);
            }
        }
        int value(int v, int x) const {
            return tree[v].order_of_key({x, -1});
        }
        int to_leaf(int i) const {
            i += 1 << __lg(2 * N - 1);
            return i < 2 * N ? i : 2 * (i - N);
        }
        //update index i to new_val
        void update(int i, int new_val) {
            assert(0 <= i && i < N);
            for(int v = (i + (1 << __lg(2 * N - 1))) % N + N; v >= 1; v >>= 1) {
                tree[v].erase({arr[i], i});
                tree[v].insert({new_val, i});
            }
            arr[i] = new_val;
        }
        //How many values in range [l, r) are < x?
        //O(log^2(n))
        int query(int l, int r, int x) const {
            // cerr<<l<<" , "<<r<<" , "<<x<<endl;
            assert(0 <= l && l <= r && r <= N);
            int res = 0;
            for (l = to_leaf(l), r = to_leaf(r); l < r; l >>= 1, r >>= 1) {
                if (l & 1) res += value(l++, x);
                if (r & 1) res += value(--r, x);
            }
            return res;
        }
    };

}; // MergeSortTree
    int dfs(vb & visited,vb & recstack,vi & v,int start,int & ctr){
        visited[start]=true;
        recstack[start]=true;
        int next=v[start];
        int root=-1;

        if(!visited[next]){
            root=dfs(visited,recstack,v,next,ctr);
        }else{
            if(recstack[next]){
                root=next;
            }
        }
        if(root != -1 && recstack[root]){
            ctr++;
        }
        recstack[start]=false;
        // cout<<" start : "<<start<<", root : "<<root<<endl;
        return root;
    }
    void solve(int testcase) {
        const int limit = 3e5 + 100;
        Sieve *sv=new Sieve(limit);
        vector<vector<int>> mp(limit);
        for (int i = 0; i < limit; i++) {
            mp[i] = vector<int>();
        }

        int n;
        cin >> n;
        vector<int> arr(n);
        for (int i = 0; i < n; i++) {
            cin >> arr[i];
            vector<int> factors = sv->getFactors(arr[i]);
            for (int fact : factors) {
                mp[fact].push_back(i);
            }
        }

        int a, b;
        cin >> a >> b;
        a--;
        b--;

        vector<vector<int>> dp(n);
        for (int i = 0; i < n; i++) {
            dp[i] = sv->getFactors(arr[i]);
        }

        int source = a;
        vector<int> dist(n, -1);
        vector<int> parent(n, -1);

        dist[source] = 0;
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        pq.push({dist[source], source});

        while (!pq.empty()) {
            int d_v = pq.top().first;
            int v = pq.top().second;
            pq.pop();
            if (d_v != dist[v]) {
                continue;
            }

            for (int fact : dp[v]) {
                for (int node : mp[fact]) {
                    if (dist[node] == -1 || dist[node] > d_v + 1) {
                        dist[node] = d_v + 1;
                        parent[node] = v;
                        pq.push({dist[node], node});
                    }
                }                    
            }
        }

        if (dist[b] == -1) {
            return reject();
        } else {
            vector<int> path;
            while (b != a) {
                path.push_back(b + 1);
                b = parent[b];
            }
            path.push_back(a + 1);
            reverse(path.begin(), path.end());
            cout << path.size() << '\n';
            for (int i = 0; i < path.size(); i++) {
                cout << path[i] << " ";
            }
            cout << '\n';
        }
    }



};

signed main(){
    FASTIO;
    BOOLALPHA;
    int t=1;
    // read(t);//isTakeTestCase
    F(i,1,t+1){
        Solution::solve(i);
    }
    return 0;
}   