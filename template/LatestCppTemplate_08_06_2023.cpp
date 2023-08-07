#include<bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp> // Common file
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/detail/standard_policies.hpp>
using namespace __gnu_pbds;
using namespace std;
template <
    typename Key, // Key type
    typename Mapped, // Mapped-policy
    typename Cmp_Fn = std::less<Key>, // Key comparison functor
    typename Tag = rb_tree_tag, // Specifies which underlying data structure to use
    template <
        typename Const_Node_Iterator,
        typename Node_Iterator,
        typename Cmp_Fn_,
        typename Allocator_ >
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


template<typename T>void read(T &a) {cin >> a;}
template<typename T>void read(T &a, T &b) {cin >> a >> b;}
template<typename T>void read(T &a, T &b, T &c) {cin >> a >> b >> c;}
template<typename T>void read(T a[], int n) {F(i, 0, n) cin >> a[i];}
template<typename T>void read(ptt & pr) {read(pr.first, pr.second);}
// template<typename T>void readv(vt & v){FEACH(a,v) read(a);}
template<typename T>void readv(vt & v, int start = 0) {
    // FEACH(a,v) read(a);
    int n = v.size();
    F(i, start, n) {
        read(v[i]);
    }
}

template<typename T>void readm(vvt & v) {FEACH(a, v) readv(a);}

void print() {cout << " " << endl;}
template<typename T>void print(T &a) {cout << a << " ";}
template<typename T>void print(T &a, T &b) {cout << a << " " << b << " ";}
template<typename T>void print(T &a, T &b, T &c) {cout << a << " " << b << " " << c << " ";}
template<typename T>void print(ptt & pr) {cout << pr.first << " " << pr.second << " ";}
void println() {cout << endl;}
template<typename T>void println(T &a) {cout << a << endl;}
template<typename T>void println(T &a, T &b) {cout << a << " " << b << endl;}
template<typename T>void println(T &a, T &b, T &c) {cout << a << " " << b << " " << c << endl;}
template<typename T>void println(ptt & pr) {cout << pr.first << " " << pr.second << endl;}
template<typename T>void println(T a[], int n) {F(i, 0, n) cout << a[i] << " "; cout << endl;}
string tostr(int a) {ostringstream ostr; ostr << a; return ostr.str();}
int tonum(string &s) {stringstream str(s); int num; str >> num; return num;}

template<typename T> void printv(vt & v) { FEACH(a, v) print(a); println();}
template<typename T> void printm(vvt & v) { FEACH(a, v) printv(a);}
void printb(bool b) {cout << b << " ";}
void printb(bool b1, bool b2) {printb(b1); printb(b2);}
void printlnb(bool b) {printb(b); println();}
void printlnb(bool b1, bool b2) {printb(b1); printb(b2); println();}
template<typename T> void send(T item) {return println(item);}
template<typename T> void sendref(T &item) {return println(item);}

using namespace std;
void reject() {
    cout << -1 << endl;
    return;
}

namespace ModuloArithmetic {
pair<long long, long long> extended_gcd(long long a, long long b) {
    if (b == 0) return{1, 1};
    pair<long long, long long> pr = extended_gcd(b, a % b);
    return {pr.second, pr.first - (a / b)*pr.second};
}
long long hcf(long long a, long long b) {
    if (a == 0 || b == 0) return max(a, b);
    pair<long long, long long> pr = extended_gcd(a, b);
    return (a * pr.first + b * pr.second);
}
long long lcm(long long a, long long b) {
    return (a * b) / (__gcd(a, b));
}
long long gcd(long long a, long long b) {
    return __gcd(a, b);
}
long long modSub(long long a, long long b, long long mod) {
    return ((a % mod - b % mod + mod) % mod);
}
long long modMul(long long a, long long b, long long mod) {
    return ((a % mod) * (b % mod)) % mod;
}
long long modAdd(long long a, long long b, long long mod) {
    return ((a % mod) + (b % mod)) % mod;
}
long long modInv(long long a, long long mod) {
    long long x, y;
    pair<long long, long long> pr = extended_gcd(a, mod);
    x = pr.first;
    y = pr.second;
    long long g = (a * x + mod * y);
    if (g != 1) {
        cerr << "modular inverse does not exist , gcd != 1" << endl;
        exit(0);
    }
    // adding m to avoid negative value of x
    long long res = (x % mod + mod) % mod;
    return res;
}
long long modDiv(long long a, long long b, long long mod) {
    a = a % mod;
    // if(a==0) return 0;
    long long inv = modInv(b, mod);
    long long res = (inv * a) % mod;
    return res;
}
long long power(long long x, unsigned long long y, long long p)
{
    long long res = 1;
    x = x % p; // Update x if it is more than or
    if (x == 0) return 0; // In case x is divisible by p;
    while (y > 0) {
        if (y & 1) res = modMul(res, x, p);
        y = y >> 1; // y = y/2
        x = modMul(x, x, p);
    }
    return res;
}
long long get_primitive_root (long long p) {
    vector<long long> fact;
    long long phi = p - 1,  n = phi;
    for (long long i = 2; i * i <= n; ++i)
        if (n % i == 0) {
            fact.push_back (i);
            while (n % i == 0)
                n /= i;
        }
    if (n > 1)
        fact.push_back (n);

    for (long long res = 2; res <= p; ++res) {
        bool ok = true;
        for (size_t i = 0; i < fact.size() && ok; ++i)
            ok &= power (res, phi / fact[i], p) != 1;
        if (ok)  return res;
    }
    return -1;
}
long long get_root_power(long long num) {
    vector<long long> powers(63);
    for (long long i = 0; i < 63; i++) {
        powers[i] = (1LL << i);
    }
    for (long long i = 62; i >= 0; i--) {
        if (num % powers[i] == 1) return i;
    }
    return -1;
}
};

namespace LangUtil {
bool isalpha(char c) {
    int ascii = (c - 'a');
    return ascii >= 0 && ascii <= 25;
}
bool isdigit(char c) {
    int ascii = (c - '0');
    return 0 <= ascii && ascii <= 9;
}
bool islower(char c) {
    return isalpha(c);
}
bool isupper(char c) {
    int ascii = (c - 'A');
    return ascii >= 0 && ascii <= 25;
}
bool isop(char c) {
    string s = "+-*/%";
    return s.find(c) != string::npos;
}
vector<string> split(string s, char delim = ' ') {
    vector<string> v;
    v.push_back("");
    for (auto c : s) {
        if (c == delim) {
            v.push_back("");
        } else {
            v.back().push_back(c);
        }

    }
    return v;
}
bool isPal(string s) {
    string first = s;
    string second = s;
    reverse(second.begin(), second.end());
    return first == second;
}
};

namespace Transformer {
inline int ctoa(char c) {
    return c - 'a';
}
inline char atoc(int a) {
    return (char)(a + 'a');
}
int ctoi(char c) {
    return c - '0';
}
char itoc(int i) {
    return i - 0 + '0';
}
char tolower(char c) {
    int ascii = (int)(c - 'A');
    char c1 = (char)(ascii + 'a');
    return c1;
}
char toupper(char c) {
    int ascii = (int)(c - 'a');
    char c1 = (char)(ascii + 'A');
    return c1;
}
};

class disjointSet {
    vector<int> ump;
public:
    vector<int>& getUmp() {
        return ump;
    }
    disjointSet(int n) {
        ump.assign(n + 1, -1);
    }
    int findSet(int u) {
        // cout<<"in findSet "<<u<<endl;
        int r = u;
        while (ump[r] >= 0) {
            r = ump[r];
        }
        while (u != r) {
            int par = ump[u];
            ump[u] = r;
            u = par;
        }
        return r;
    }
    bool setUnion(int u, int v) {
        // cout<<"in setUnion "<<u<<" "<<v<<endl;
        int uroot = findSet(u);
        int vroot = findSet(v);
        // cout<<"root : "<<uroot<<" "<<vroot<<endl;
        if (uroot == vroot) return false;
        int uchild = ump[uroot];
        int vchild = ump[vroot];
        int totalChild = uchild + vchild;

        if (uchild > vchild) {
            ump[uroot] = vroot;
            ump[vroot] = totalChild;
        } else {
            ump[vroot] = uroot;
            ump[uroot] = totalChild;
        }
        return true;
    }
    bool prefered_union(int u, int v) {
        int uroot = findSet(u);
        int vroot = findSet(v);
        if (uroot == vroot) return false;
        int uchild = ump[uroot];
        int vchild = ump[vroot];
        int totalChild = uchild + vchild;
        ump[uroot] = vroot;
        ump[vroot] = totalChild;
        return true;
    }
    bool checkOdd(int l, int r) {
        for (int i = l; i <= r; i++) {
            // cout<<ump[i]<<" ";
            if (ump[i] < 0) {
                if (abs(ump[i]) % 2) return false;
            }
        }
        // cout<<endl;
        return true;
    }

    int getChilds(int u) {
        int root = findSet(u);
        return abs(ump[root]);
    }
};


class Sieve {
public:
    vector<int> primes;

    vector<int> lp;
    int n = 1e5 + 10;
    Sieve() {
        init();
    }
    Sieve(int n) {
        this->n = n;
        init();
    }
    void init() {
        vector<bool> isprm(n, true);
        lp.assign(n, -1);

        isprm[0] = isprm[1] = false;
        for (int i = 2; i < n; i++) {
            if (isprm[i] == false) continue;
            lp[i] = i;
            primes.push_back(i);

            for (int j = i + i; j < n; j += i) {
                isprm[j] = false;
                if (lp[j] == -1) {
                    lp[j] = i;
                }

            }
        }
        // printv(lp);
    }
    vector<int> & get() {
        return primes;
    }
    int getLP(int num) {
        return this->lp[num];
    }
    bool isPrime(int num) {
        return (lp[num] == num);
    }
    vector<int> getFactors(int num) {

        set<int> factors;
        while (num > 1) {
            factors.insert(lp[num]);
            num /= lp[num];
        }

        vector<int> facts;
        for (auto & prm : factors) facts.push_back(prm);
        return facts;
    }
    void print() {
        for (auto &prm : primes) cout << prm << " "; cout << endl;
    }
    static void how_to_use() {
        int limit = 1e5 + 10;
        Sieve *sv = new Sieve(limit);
        vector<int> factors = sv->getFactors(100);
        for (auto fact : factors) cout << fact << " "; cout << endl;
        //logs : 2 5
    }
};

// fenwick tree
class fenwickTree {
    vector<int> BIT;
    int n;
public :
    fenwickTree(int n) {
        this->n = n;
        // BIT=*new vector<int>(n,0);
        BIT.assign(n, 0);
    }
    fenwickTree(int *arr, int n) {

        this->n = n;
        BIT = *new vector<int>(n, 0);
        BIT[0] = arr[0];
        for (int i = 1; i < n; i++) {
            this->update(i, arr[i]);
        }
    }
    fenwickTree(vector<int>&v) {
        this->n = v.size();
        BIT = *new vector<int>(n, 0);
        BIT[0] = v[0];
        for (int i = 1; i < n; i++) {
            this->update(i, v[i]);
        }
    }
    void update(int index, int delta)
    {
        if (index == 0) {BIT[index] += delta; return;}
        for (; index < n; index += index & -index)

            BIT[index] += delta;
    }
    int get(int index)
    {
        int sum = BIT[0];
        for (; index > 0; index -= index & -index)
            sum += BIT[index];
        return sum;
    }
    void print() {
        for (int i = 0; i < n; i++) {
            cout << BIT[i] << " ";
        }
        cout << endl;
    }
    int size() {
        return this->n;
    }
};




using namespace ModuloArithmetic;

using namespace Transformer;


void flip(string & s, int limit) {
    F(i, 0, limit) {
        s[i] = (s[i] ^ 1);
    }
}
bool check_border(int i, int j, int n, int m) {
    return i >= 0 && j >= 0 && i < n && j < m;
}
int get_linear_index(int i, int j, int m) {
    return i * m + j;
}

int kadene(vi & v) {
    int n = v.size();
    int mx_so_far = 0;
    int mx = 0;
    FEACH(num, v) {
        mx_so_far = max(mx_so_far, 0LL);
        mx_so_far += num;
        mx = max(mx, mx_so_far);
    }
    return mx;
}


class NCRefficient {
public :
    int n, mod, r;
    vector<int> fact, invFact, invNum;
    void calculateFactorial() {
        fact[0] = fact[1] = 1;
        for (int i = 2; i <= n; i++) {
            fact[i] = (fact[i - 1] * i) % mod;
        }
        return;
    }
    void calculateInverseNum() {
        invNum[0] = invNum[1] = 1;
        for (int i = 2; i <= n; i++) {
            invNum[i] = invNum[mod % i] * (mod - mod / i) % mod;
        }
    }
    void calculateInverseFactorial() {
        invFact[0] = invFact[1] = 1;
        for (int i = 2; i <= n; i++) {
            invFact[i] = (invNum[i] * invFact[i - 1]) % mod;
        }
    }
    NCRefficient(int n, int mod): n(n), mod(mod) {
        fact.resize(n + 1);
        invFact.resize(n + 1);
        invNum.resize(n + 1);
        this->calculateFactorial();
        this->calculateInverseNum();
        this->calculateInverseFactorial();
    }
    int get(int N, int r) {
        if (N > n) return 0;
        if (r < 0 || r > N) return 0;
        int ans = (fact[N] * invFact[r]) % mod * (invFact[N - r]) % mod;
        return ans;
    }
};

class LCABinaryLifting {
public:
    int n;
    int timer = 0;
    vector<vector<int>> graph;
    vector<int> tin, tout;
    vector<vector<int>> up;
    int height = 0;
    int root = 0;
    LCABinaryLifting(vector<vector<int>> & graph, int root) {
        this->n = (int)(graph.size());
        this->timer = 0;
        this->graph = graph;
        this->tin.resize(n + 1);
        this->tout.resize(n + 1);
        this->height = ceil(log2(n + 1));
        this->root = root;
        this->up.assign(n + 1, vector<int>(height + 1));
        visit(root, root);
    }
    void visit(int u, int parent) {
        timer++;
        tin[u] = timer;
        up[u][0] = parent;
        for (int i = 1; i <= height; i++) {
            up[u][i] = up[up[u][i - 1]][i - 1];
        }
        for (auto node : graph[u]) {
            if (node != parent) {
                visit(node, u);
            }
        }
        tout[u] = timer;
    }
    inline bool isAnsestor(int u, int v) {
        return (tin[u] <= tin[v] && tout[u] >= tout[v]);
    }
    int getLCA(int u, int v) {
        if (isAnsestor(u, v)) return u;
        if (isAnsestor(v, u)) return v;
        for (int i = height; i >= 0; i--) {
            if (false == isAnsestor(up[u][i], v)) {
                u = up[u][i];
            }
        }
        return up[u][0];
    }
    // user manual
    static void how_to_use() {
        int n, m;
        cin >> n >> m;
        int root;
        cin >> root;
        vector<vector<int>> graph(n + 1);
        for (int i = 0; i < m; i++) {
            int u, v;
            cin >> u >> v;
            graph[u].push_back(v);
            graph[v].push_back(u);
        }
        LCABinaryLifting *lbt = new LCABinaryLifting(graph, root);

        int q;
        cin >> q;
        for (int i = 0; i < q; i++) {
            int u, v;
            cin >> u >> v;
            int anc = lbt->getLCA(u, v);
            cout << "u: " << u << " ,v: " << v << " ,anc = " << anc << endl;
        }
        delete lbt;
    }
};
class LazySegmentTree {
    int n = 0;
    int MYSIZE = 0;
    vector<long long> tree, lazy;
    vector<long long> arr;
public:
    void init(int n) {
        this->n = n;
        this->MYSIZE = 4 * n + 10;
        tree.assign(MYSIZE, 0LL);
        lazy.assign(MYSIZE, 0LL);
        arr.assign(MYSIZE, 0LL);
    }
    void post_init() {
        this->constructST();
    }
    LazySegmentTree(vector<int> & v) {
        int n = v.size();
        init(n);
        for (int i = 0; i < n; i++) {
            arr[i] = v[i];
        }
        post_init();
    }
    LazySegmentTree(int v[], int n) {
        init(n);
        for (int i = 0; i < n; i++) {
            arr[i] = v[i];
        }
        post_init();
    }
    LazySegmentTree(int n) {
        init(n);
        post_init();
    }
    void updateRangeUtil(int si, int ss, int se, int us,
                         int ue, int diff)
    {
        if (lazy[si] != 0)
        {
            tree[si] += (se - ss + 1) * lazy[si];
            if (ss != se)
            {
                lazy[si * 2 + 1]   += lazy[si];
                lazy[si * 2 + 2]   += lazy[si];
            }
            lazy[si] = 0;
        }
        if (ss > se || ss > ue || se < us)
            return ;
        if (ss >= us && se <= ue)
        {
            tree[si] += (se - ss + 1) * diff;
            if (ss != se)
            {
                lazy[si * 2 + 1]   += diff;
                lazy[si * 2 + 2]   += diff;
            }
            return;
        }
        int mid = (ss + se) / 2;
        updateRangeUtil(si * 2 + 1, ss, mid, us, ue, diff);
        updateRangeUtil(si * 2 + 2, mid + 1, se, us, ue, diff);
        tree[si] = tree[si * 2 + 1] + tree[si * 2 + 2];
    }
    void updateRange(int us, int ue, int diff)
    {
        updateRangeUtil(0, 0, n - 1, us, ue, diff);
    }
    void update(int us, int ue, int diff) {
        updateRange(us, ue, diff);
    }
    void update(int us, int diff) {
        updateRange(us, us, diff);
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
            tree[si] += (se - ss + 1) * lazy[si];
            if (ss != se)
            {
                lazy[si * 2 + 1] += lazy[si];
                lazy[si * 2 + 2] += lazy[si];
            }
            lazy[si] = 0;
        }
        if (ss > se || ss > qe || se < qs)
            return 0;
        if (ss >= qs && se <= qe)
            return tree[si];
        int mid = (ss + se) / 2;
        return getSumUtil(ss, mid, qs, qe, 2 * si + 1) +
               getSumUtil(mid + 1, se, qs, qe, 2 * si + 2);
    }
    int getSum(int qs, int qe)
    {
        if (qs < 0 || qe > n - 1 || qs > qe)
        {
            printf("Invalid Input");
            return -1;
        }
        return getSumUtil(0, n - 1, qs, qe, 0);
    }
    int query(int qs, int qe) {
        return getSum(qs, qe);
    }
    void constructSTUtil(int ss, int se, int si)
    {
        if (ss > se)
            return ;
        if (ss == se) {
            tree[si] = arr[ss];
            return;
        }
        int mid = (ss + se) / 2;
        if (ss <= mid) constructSTUtil(ss, mid, si * 2 + 1);
        if (mid + 1 <= se) constructSTUtil(mid + 1, se, si * 2 + 2);
        tree[si] = tree[si * 2 + 1] + tree[si * 2 + 2];
    }
    void constructST() {
        constructSTUtil(0, n - 1, 0);
    }
};
class HLD {
    vector<int> parent, depth, heavy, head, pos;
    vector<vector<int>> graph;
    vector<int> vals;
    int n = 0;
    int curr_pos = 0;
    LazySegmentTree *st = NULL;
public:
    HLD(vector<vector<int>> & graph, vector<int>& vals) {
        this->graph = graph;
        this->n = this->graph.size();
        this->vals = vals;
        init();
    }
    int dfsTrip(int start) {
        int subtreeSize = 1;
        int maxChildSubtreeSize = 0;
        for (auto & node : graph[start]) {
            if (parent[start] != node) {
                parent[node] = start;
                depth[node] = depth[start] + 1;
                int childSubtreeSize = dfsTrip(node);
                subtreeSize += childSubtreeSize;
                if (childSubtreeSize > maxChildSubtreeSize) {
                    maxChildSubtreeSize = childSubtreeSize;
                    heavy[start] = node;
                }
            }
        }
        return subtreeSize;
    }
    void decompose(int start, int leader) {
        head[start] = leader;
        pos[start] = curr_pos++;
        if (heavy[start] != -1) {
            decompose(heavy[start], leader);
        }
        for (auto & node : graph[start]) {
            if (parent[start] != node && heavy[start] != node) {
                decompose(node, node);
            }
        }
    }
    void init() {
        this->parent.assign(n, -1);
        this->depth.assign(n, 0);
        this->heavy.assign(n, -1);
        this->head.assign(n, -1);
        this->pos.assign(n, 0);
        this->curr_pos = 0;
        dfsTrip(0);
        decompose(0, 0);
        initializeSegmentTree();
    }
    int query(int a, int b) {
        // cout<<"a : "<<a<<" , b : "<<b<<endl;
        int res = 0;
        for (; head[a] != head[b]; b = parent[head[b]]) {
            // cout<<"in for loop : "<<" a : "<<a<<" , b : "<<b<<endl;

            if (depth[head[a]] > depth[head[b]]) {
                swap(a, b);
            }
            // cout<<"getting query from : "<<head[b]<<" , "<<b<<endl;

            int currHeavyPathRes = st->query(pos[head[b]], pos[b]);
            // cout<<"pos from : "<<pos[head[b]]<<" , "<<pos[b]<<" with val : "<<currHeavyPathRes<<endl;
            // res=max(res,currHeavyPathRes);
            res += currHeavyPathRes;
        }
        // cout<<"out for loop : "<<" a : "<<a<<" , b : "<<b<<endl;
        if (depth[a] > depth[b]) {
            swap(a, b);
        }
        int lastHeavyPathRes = st->query(pos[a], pos[b]);
        // res=max(res,lastHeavyPathRes);
        res += lastHeavyPathRes;
        // cout<<"query : "<<a<<" , "<<b<<" : "<<res<<endl;
        // cout<<"pos : "<<pos[a]<<" , "<<pos[b]<<endl;
        return res;
    }
    void initializeSegmentTree() {
        this->st = new LazySegmentTree(n);
        for (int i = 0; i < n; i++) {
            this->st->updateRange(pos[i], pos[i], vals[i]);
        }
    }
    void update(int a, int b, int delta) {
        for (; head[a] != head[b]; b = parent[head[b]]) {
            if (depth[head[a]] > depth[head[b]]) {
                swap(a, b);
            }
            st->updateRange(pos[head[b]], pos[b], delta);
        }
        if (depth[a] > depth[b]) {
            swap(a, b);
        }
        this->st->updateRange(pos[a], pos[b], delta);
    }
    void print() {
        printv(head);
        printv(parent);
        printv(heavy);
        printv(depth);
        printv(vals);
    }
    static void how_to_use() {
        int n;
        cin >> n;
        int m;
        cin >> m;
        vector<vector<int>> graph(n);
        for (int i = 0; i < m; i++) {
            int u, v;
            cin >> u >> v;
            graph[u].push_back(v);
            graph[v].push_back(u);
        }
        vector<int> vals(n, -1);
        for (int i = 0; i < n; i++) {
            vals[i] = i;
        }
        HLD *hld = new HLD(graph, vals);
        hld->print();
        int q;
        cin >> q;
        for (int i = 0; i < q; i++) {
            int u, v;
            cin >> u >> v;

            int ans = hld->query(u, v);
            cout << u << " , " << v << " : ";
            cout << ans << endl;
        }
        delete hld;
    }
};
class LazySegmentTreeWithSetUpdate {
    int n = 0;
    int MYSIZE = 0;
    vector<long long> tree, lazy, stamp;
    vector<bool> pending;
    vector<long long> arr;
    int tm = 0;
public:
    void init(int n) {
        this->n = n;
        this->MYSIZE = 4 * n + 10;
        tree.assign(MYSIZE, 0LL);
        lazy.assign(MYSIZE, 0LL);
        arr.assign(MYSIZE, 0LL);
        stamp.assign(MYSIZE, 0LL);
        pending.assign(MYSIZE, false);
    }
    void post_init() {
        this->constructST();
    }
    LazySegmentTreeWithSetUpdate(vector<int> & v) {
        int n = v.size();
        init(n);
        for (int i = 0; i < n; i++) {
            arr[i] = v[i];
        }
        post_init();
    }
    LazySegmentTreeWithSetUpdate(int v[], int n) {
        init(n);
        for (int i = 0; i < n; i++) {
            arr[i] = v[i];
        }
        post_init();
    }
    LazySegmentTreeWithSetUpdate(int n) {
        init(n);
        post_init();
    }
    void updateRangeUtil(int si, int ss, int se, int us,
                         int ue, int diff, int stamp_value)
    {
        if (pending[si])
        {
            tree[si] = (se - ss + 1) * lazy[si];
            if (ss != se)
            {
                if (stamp[si * 2 + 1] <= stamp[si]) {
                    lazy[si * 2 + 1]   = lazy[si];
                    stamp[si * 2 + 1]   = stamp[si];
                    pending[si * 2 + 1] = true;
                }
                if (stamp[si * 2 + 2] <= stamp[si]) {
                    lazy[si * 2 + 2]   = lazy[si];
                    stamp[si * 2 + 2]   = stamp[si];
                    pending[si * 2 + 2] = true;
                }
            }
            pending[si] = false;
        }
        if (ss > se || ss > ue || se < us)
            return ;
        if (ss >= us && se <= ue)
        {
            tree[si] = (se - ss + 1) * diff;
            if (ss != se)
            {
                if (stamp[si * 2 + 1] <= stamp_value) {
                    lazy[si * 2 + 1]   = diff;
                    stamp[si * 2 + 1]   = stamp_value;
                    pending[si * 2 + 1] = true;
                }
                if (stamp[si * 2 + 2] <= stamp_value) {
                    lazy[si * 2 + 2]   = diff;
                    stamp[si * 2 + 2]   = stamp_value;
                    pending[si * 2 + 2] = true;
                }
            }
            stamp[si] = stamp_value;
            return;
        }
        int mid = (ss + se) / 2;
        updateRangeUtil(si * 2 + 1, ss, mid, us, ue, diff, stamp_value);
        updateRangeUtil(si * 2 + 2, mid + 1, se, us, ue, diff, stamp_value);
        tree[si] = tree[si * 2 + 1] + tree[si * 2 + 2];
    }
    void updateRange(int us, int ue, int diff)
    {
        ++tm;
        updateRangeUtil(0, 0, n - 1, us, ue, diff, tm);
    }
    void update(int us, int ue, int diff) {
        updateRange(us, ue, diff);
    }
    int getSumUtil(int ss, int se, int qs, int qe, int si)
    {
        if (pending[si])
        {

            tree[si] = (se - ss + 1) * lazy[si];
            if (ss != se)
            {
                if (stamp[si * 2 + 1] <= stamp[si]) {
                    lazy[si * 2 + 1] = lazy[si];
                    stamp[si * 2 + 1] = stamp[si];
                    pending[si * 2 + 1] = true;
                }
                if (stamp[si * 2 + 2] <= stamp[si]) {
                    lazy[si * 2 + 2] = lazy[si];
                    stamp[si * 2 + 2] = stamp[si];
                    pending[si * 2 + 2] = true;
                }
            }
            pending[si] = false;
        }
        if (ss > se || ss > qe || se < qs)
            return 0;
        if (ss >= qs && se <= qe)
            return tree[si];
        int mid = (ss + se) / 2;
        return getSumUtil(ss, mid, qs, qe, 2 * si + 1) +
               getSumUtil(mid + 1, se, qs, qe, 2 * si + 2);
    }
    int getSum(int qs, int qe)
    {
        if (qs < 0 || qe > n - 1 || qs > qe)
        {
            printf("Invalid Input");
            return -1;
        }
        return getSumUtil(0, n - 1, qs, qe, 0);
    }
    int query(int qs, int qe) {
        return getSum(qs, qe);
    }
    void constructSTUtil(int ss, int se, int si)
    {
        if (ss > se)
            return ;
        if (ss == se) {
            tree[si] = arr[ss];
            return;
        }
        int mid = (ss + se) / 2;
        if (ss <= mid) constructSTUtil(ss, mid, si * 2 + 1);
        if (mid + 1 <= se) constructSTUtil(mid + 1, se, si * 2 + 2);
        tree[si] = tree[si * 2 + 1] + tree[si * 2 + 2];
    }
    void constructST() {
        constructSTUtil(0, n - 1, 0);
    }
    static void how_to_use() {
        vector<int> arr = {1, 2, 3, 4};
        LazySegmentTreeWithSetUpdate *mylst = new LazySegmentTreeWithSetUpdate(arr);
        mylst->update(0, 3, 0);
        mylst->update(2, 3, 2);
        mylst->update(0, 2, 10);
        int ans = mylst->query(1, 2);
        cout << ans << endl;
    }
};
using namespace LangUtil;


class InteractiveJudge {
public:
    bool mock=true;
    int maxQueryLimit=0;


    vector<int> hidden;

    InteractiveJudge(bool mock,int maxQueryLimit,vector<int> hidden){
        this->hidden=hidden;
        this->mock=mock;
        this->maxQueryLimit=maxQueryLimit;
        init();
    }

    void init(){
        if(mock){
            // this can be mocked .... 
            for(int i=0;i<hidden.size();i++){
                cin>>hidden[i];
            }
        }
    }

    void validate(){
        if(maxQueryLimit<=0){
            cout<<"Max Query Limit Exceeded"<<endl;
            exit(0);
        }
    }

    void query(vector<int> & query,int & response){

        validate();
        maxQueryLimit--;

        if(mock){
            response=mockQuery(query);
        }else{
            printQuery(query);
            readResponse(response);
        }
    }

    int mockQuery(vector<int> & query){
        // perform query operation and return result
        // this processing should be dynamic .... 

        int xorr=0;
        for(auto index:query){
            xorr^=(hidden[index-1]);
        }

        return xorr;
    }


    void printQuery(vector<int> & query){
        cout<<"? ";
        for(auto num:query){
            cout<<num<<" ";
        }
        cout<<endl;
    }

    void guess(const vector<int> & guessed){
        if(mock){
            mockGuess(guessed);
        }else{
            printGuess(guessed);
        }
    }

    void mockGuess(const vector<int> & guessed){
        bool result =(hidden==guessed);
        cout<<"result : "<<result<<endl;
    }


    void printGuess(const vector<int> & guessed){
        cout<<"! ";
        for(auto num:guessed){
            cout<<num<<" ";
        }
        cout<<endl;
    }

    void readResponse(int & response){
        cin>>response;
    }

    static void how_to_use(){
        bool mock=true;
        int maxQueryLimit=10;

        vector<int> hidden={1,0,1};

        InteractiveJudge *judge=new InteractiveJudge(mock,maxQueryLimit,hidden);

        // take some input here
        vector<int> que={1,2};
        
        int response;

        judge->query(que,response);

        cout<<"response : "<<response<<endl;

        judge->guess(vector<int>{1,0,1});
    }
};

namespace Solution {

    void solve(int testcase) {

        int n, k;
        read(n, k);

        bool mock=false;
        int maxQueryLimit=n;
        
        vector<int> hidden(n);

        InteractiveJudge *judge=new InteractiveJudge(mock,maxQueryLimit,hidden);
        

        vector<int> query;
        for(int i=0;i<k;i++){
            query.push_back(i+1);
        }

        vector<int> guess(n,-1);
        vector<int> responses(n,0);

        int xorr=0;

        for(int i=0;i<=k;i++){
            judge->query(query,responses[i]);
            
            xorr^=responses[i];
            
            // print(responses[i]);print(" : ");printv(query);

            for(auto & num:query) num=num%(k+1) + 1;
        }


        for(int i=0;i<=k;i++){
            guess[i]=xorr^(responses[(i+1)%(k+1)]);
        }

        // printv(guess);


        
        int prefXor=0;
        for(int i=0;i<k-1;i++){
            prefXor^=guess[i];
            query[i]=i+1;
        }
        
        // cout<<prefXor<<" : prefXor "<<endl;

        for(int i=k+1;i<n;i++){
            query.back()=i+1;

            judge->query(query,responses[i]);

            // print(responses[i]);print(" : ");printv(query);

            guess[i]=prefXor ^ responses[i];
        }

        // printv(guess);

        judge->guess(guess);

        delete judge;
    }
};

signed main() {
    // FASTIO;
    BOOLALPHA;
    int t = 1;
    // read(t);//isTakeTestCase
    F(i, 1, t + 1) {
        Solution::solve(i);
    }
    return 0;
}