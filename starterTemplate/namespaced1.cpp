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
    int power(long long x, unsigned int y, int p) 
    { 
        int res = 1; 
        x = x % p; // Update x if it is more than or 
        if (x == 0) return 0; // In case x is divisible by p;
        while (y > 0) { 
            if (y & 1) res = (res*x) % p; 
            y = y>>1; // y = y/2 
            x = (x*x) % p; 
        } 
        return res; 
    }
};
     
class LangUtil{
public:
    static bool isalpha(char c){
        int ascii=(c-'a');
        return ascii>=0 && ascii<=25;
    }    
    static bool isdigit(char c){
        int ascii=(c-'0');
        return 0<=ascii && ascii<=9;
    }
    static bool islower(char c){
        return isalpha(c);
    }
    static bool isupper(char c){
        int ascii=(c-'A');
        return ascii>=0 && ascii<=25;
    }
    static bool isop(char c){
        string s="+-*/%";
        return s.find(c) != string::npos;
    }
    static vector<string> split(string s,char delim=' '){
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
};

class Transformer{
public: 
    static int ctoi(char c){
        return c-'0';
    }
    static char itoc(int i){
        return i-0+'0';
    }
    static char tolower(char c){
        int ascii=(int)(c-'A');
        char c1=(char)(ascii+'a');
        return c1;
    }
    static char toupper(char c){
        int ascii=(int)(c-'a');
        char c1=(char)(ascii+'A');
        return c1;
    }
};
class Calc{
public:
    static double eval(double a,double b,char op){
        double res=0.0;
        if(op=='+') res=a+b;
        else if(op=='-') res=a-b;
        else if(op=='*') res=a*b;
        else if(op=='/') res=a/b;
        
        return res;
    }
    static int modulo(int a,int b){
        return a%b;
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
class Factorial{
    public:
    vector<long long> fact;
    long long mod=(1e9)+7;
    long long sz=0;
    Factorial(long long n,long long mod=(int)(1e9+7)){
        this->sz=n+10;
        this->fact.resize(sz);
        this->mod=mod;
        init();
    }
    void init(){
        fact[0]=1;
        for(int i=1;i<sz;i++){
            fact[i]=((fact[i-1]%mod)*(i%mod))%mod;
        }
    }
    long long get(int n){
        return this->fact[n];
    }
};
class RandomEngine{

    mt19937 mt;
public:
    RandomEngine(){
        mt19937 smt(time(nullptr));
        this->mt=smt;
    }
    RandomEngine(int seed){
        mt19937 smt(seed);
        this->mt=smt;   
    }
    int get(){
        return mt();
    }
    int get(int n){
        return get()%n;
    }
    int get(int l,int r){
        int window=r-l+1;
        return get(window)+l;
    }
    vector<int> get_random_vector(int n){
        vector<int> v(n);
        disjointSet *ds=new disjointSet(n+1);
        F(i,0,n){
            int rem=n-i;
            int index=get(rem);
            int root=ds->findSet(index);
            ds->prefered_union(root,root+1);
            v[i]=root;
        }
        // printv(v);
        delete ds;
        return v;
    }
    static void how_to_use(){
        RandomEngine *rng=new RandomEngine();
        cout<<rng->get()<<endl;
        cout<<rng->get(10)<<endl;
        cout<<rng->get(20,30)<<endl;
    }
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
class HLD{
    vector<int> parent,depth,heavy,head,pos;
    vector<vector<int>> graph;
    vector<int> vals;
    int n=0;
    int curr_pos=0;
    MaxLazySegmentTree *st=NULL;
public: 
    HLD(vector<vector<int>> & graph,vector<int>& vals){
        this->graph=graph;
        this->n=this->graph.size();
        this->vals=vals;
        init();
    }
    int dfsTrip(int start){
        int subtreeSize=1;
        int maxChildSubtreeSize=0;
        for(auto & node: graph[start]){
            if(parent[start] != node){
                parent[node]=start;
                depth[node]=depth[start]+1;
                int childSubtreeSize=dfsTrip(node);
                subtreeSize+=childSubtreeSize;
                if(childSubtreeSize>maxChildSubtreeSize){
                    maxChildSubtreeSize=childSubtreeSize;
                    heavy[start]=node;
                }
            }
        }
        return subtreeSize;
    }
    void decompose(int start,int leader){
        head[start]=leader;
        pos[start]=curr_pos++;
        if(heavy[start]!=-1){
            decompose(heavy[start],leader);
        }
        for(auto & node:graph[start]){
            if(parent[start] != node && heavy[start] != node){
                decompose(node,node);
            }
        }
    }
    void init(){
        this->parent.assign(n,-1);
        this->depth.assign(n,0);
        this->heavy.assign(n,-1);
        this->head.assign(n,-1);
        this->pos.assign(n,0);
        this->curr_pos=0;
        dfsTrip(0);
        decompose(0,0);
        initializeSegmentTree();
    }
    int query(int a,int b){
        // cout<<"a : "<<a<<" , b : "<<b<<endl;
        int res=0;
        for(;head[a] != head[b];b=parent[head[b]]){
            // cout<<"in for loop : "<<" a : "<<a<<" , b : "<<b<<endl;

            if(depth[head[a]]>depth[head[b]]){
                swap(a,b);
            }
            // cout<<"getting query from : "<<head[b]<<" , "<<b<<endl;

            int currHeavyPathRes=st->getMax(pos[head[b]],pos[b]);
            // cout<<"pos from : "<<pos[head[b]]<<" , "<<pos[b]<<" with val : "<<currHeavyPathRes<<endl;
            res=max(res,currHeavyPathRes);
        }
        // cout<<"out for loop : "<<" a : "<<a<<" , b : "<<b<<endl;
        if(depth[a]>depth[b]){
            swap(a,b);
        }
        int lastHeavyPathRes=st->getMax(pos[a],pos[b]);
        res=max(res,lastHeavyPathRes);
        // cout<<"query : "<<a<<" , "<<b<<" : "<<res<<endl;
        // cout<<"pos : "<<pos[a]<<" , "<<pos[b]<<endl;
        return res;
    }
    void initializeSegmentTree(){
        this->st=new MaxLazySegmentTree(n);
        for(int i=0;i<n;i++){
            this->st->updateRange(pos[i],pos[i],vals[i]);
        }
    }
    void print(){
        printv(head);
        printv(parent);
        printv(heavy);
        printv(depth);
        printv(vals);
        // for(int i=0;i<n;i++){
        //     cout<<"i : "<<i<<" , pos[i] : "<<pos[i]<<" , vals[i] : "<<st->getMax(i,i)<<endl;
        // }
    }
    static void how_to_use(){
        int n;
        cin>>n;
        int m;
        cin>>m;
        vector<vector<int>> graph(n);
        for(int i=0;i<m;i++){
            int u,v;
            cin>>u>>v;
            graph[u].push_back(v);
            graph[v].push_back(u);
        }
        vector<int> vals(n,-1);
        for(int i=0;i<n;i++){
            vals[i]=i;
        }
        HLD *hld=new HLD(graph,vals);
        hld->print();
        int q;
        cin>>q;
        for(int i=0;i<q;i++){
            int u,v;
            cin>>u>>v;
            
            int ans=hld->query(u,v);
            cout<<u<<" , "<<v<<" : ";
            cout<<ans<<endl;
        }
        delete hld;
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
    
};
class CordinateCompressor{
public:
    map<int,int> cord;
    vector<int> reverseCord;
    vector<int> arr;
    int n;
    CordinateCompressor(vector<int> & arr){
        this->arr=arr;
        this->n=this->arr.size();
        this->reverseCord.assign(n+10,-1);
        startCompressor();
    }
    void startCompressor(){
        sort(arr.begin(),arr.end());
        int key=1;
        for(auto& val:arr){
            if(cord.count(val)==0){
                cord[val]=key;
                reverseCord[key]=val;
                key++;    
            }
        }
    }
    int compress(int num){
        if(cord.count(num)==0) return -1;
        return cord[num];
    }
    int decompress(int num){
        return reverseCord[num];
    }
    static void how_to_use(){
        // println("shree ganeshay namah");
        vector<int> arr={100,10,52,83,10};
        int len=arr.size();
        CordinateCompressor * cc=new CordinateCompressor(arr);
        vector<int> compressed(len),decompressed(len);
        for(int i=0;i<len;i++){
            compressed[i]=cc->compress(arr[i]);
            decompressed[i]=cc->decompress(compressed[i]);
            cout<<"element : "<<arr[i]<<" : ";
            cout<<compressed[i]<<" , "<<decompressed[i]<<endl;
        }
        
        delete cc;
    }
};
class InversionCounter{
public:
    vector<int> arr;
    int n;
    int ctr=0;

    InversionCounter(vector<int> & v){
        this->arr=v;
        this->n=arr.size();
        this->ctr=0;
        process();
    }
    void process(){
        startCounting();
    }
    void startCounting(){
        int len=n+10;
        fenwickTree *fnt=new fenwickTree(len);
        CordinateCompressor *cc=new CordinateCompressor(arr);
        this->ctr=0;
        for(auto elem:arr){
            int key=cc->compress(elem);
            int diff=(fnt->get(len-1)-fnt->get(key));
            this->ctr+=diff;
            fnt->update(key,1LL);
        }
        delete cc;
        delete fnt;
    }
    int getCount(){
        return ctr;
    }
    static void how_to_use(){
        vector<int> arr={100,10,10,10,10};
        InversionCounter *ic=new InversionCounter(arr);
        int inversion=ic->getCount();
        cout<<"inversion : "<<inversion<<endl;
        delete ic;
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

namespace MathUtil{
    bool isPrime(int n){
        int limit=sqrt(n)+1;
        if(n%2==0) return false;
        for(int i=3;i<limit;i+=2){
            if(n%i==0) return false;
        }
        return true;
    }
    int sumOfDigits(int n){
        vi v;
        while(n>0){
            v.pb(n%10);
            n/=10;
        }
        int mult=1;
        int sz=v.size();
        int total=accumulate(ALL(v),0);
        return total;
    }
} 
namespace CommonUtil{
    void printKickStartCase(int t){
        cout<<"Case #"<<t<<": ";
    }
    void printTime(){
        double tm=(float)clock()/CLOCKS_PER_SEC;
        cerr<<"time taken : "<<tm<<endl;
    }
}  


using namespace ModuloArithmetic;
using namespace CommonUtil;
using namespace MathUtil;

int doit(vi & v,int m){
    vi pref=v;
    int n=v.size();
    F(i,1,n){
        pref[i]+=pref[i-1];
    }
    priority_queue<int> pq;
    int upto=0;
    int ctr=0;
    F(i,0,n){
        upto+=v[i];
        pq.push(-v[i]);
        cout<<"at i : "<<i<<" , upto : "<<upto<<" vs critical : "<<pref[m-1]<<endl;
        while(pq.size()>0 && upto<pref[m-1]){
            int major=pq.top();
            cout<<"using major : "<<major<<endl;
            pq.pop();
            upto+=2*major;
            ctr++;
        }
        if(upto<pref[m-1]) return 1e15;
    }
    return ctr;
}

void solve(int t){
    int n;
    read(n);
    int limit;
    read(limit);
    
    int base=1;
    int ctr=0;
    while(sumOfDigits(n)>limit){
        // cout<<"dtos : "<<dtos(n)<<" , limit : "<<limit<<endl;
        int digit=(n/base)%10;
        if(digit>0){
            int addon=(10-digit)*base;
            n+=addon;
            ctr+=addon;
        }
        base*=10;
    }
    println(ctr);
}

signed main(){
    FASTIO;
    BOOLALPHA;
    int t=1;
    read(t);//isTakeTestCase
    F(i,1,t+1){
        solve(i);
    }
    printTime();
    return 0;
}   


