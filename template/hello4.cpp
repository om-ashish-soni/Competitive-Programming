#include<bits/stdc++.h>
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
using namespace std;
template<typename T>void read(T &a){cin>>a;}
template<typename T>void read(T &a,T &b){cin>>a>>b;}
template<typename T>void read(T &a,T &b,T &c){cin>>a>>b>>c;}
template<typename T>void read(T a[],int n){F(i,0,n) cin>>a[i];}
template<typename T>void readv(vt & v){FEACH(a,v) read(a);}
template<typename T>void readm(vvt & v){FEACH(a,v) readv(a);}
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
template<typename T> void printm(vvt & v){ FEACH(a,v) printv(a);}
void printb(bool b){cout<<b<<" ";}
void printb(bool b1,bool b2){printb(b1);printb(b2);}
void printlnb(bool b){printb(b);println();}
void printlnb(bool b1,bool b2){printb(b1);printb(b2);println();}
inline int getseginf(){return INF4;}
template<typename T>T PERFORM(T a,T b,char op){
    if(op=='+') return a+b;
    else if(op=='m') return max(a,b);
    else if(op=='n') return min(a,b);
    else if(op=='|') return a|b;
    else if(op=='&') return a&b;
    else if(op=='^') return a^b;
    else if(op=='g') return GCD(a,b);
    else if(op=='l') return LCM(a,b);
    else if(op=='-') return a-b;
    else if(op=='*') return a*b;
    else if(op=='/') return a/b;
    return -1;
}
int IDENTITY(char op){
    if(op=='+' || op=='|' || op=='^' || op=='-' ) return 0;
    else if(op=='m') return 0LL-getseginf();
    else if(op=='n') return getseginf();
    else if(op=='g') return 0LL;
    else if(op=='l') return 1LL;
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

template<typename T>bool COMPARE(T & a,T & b,char op){
    if(op=='m') return a>b;
    else if(op=='n') return a<b;
    return a==b;
}
template<typename T>ptt COMBINE(ptt & a,ptt & b,char op){
    bool resm=COMPARE(a.first,b.first,'m');
    bool resn=COMPARE(a.first,b.first,'n');
    if(op=='m'){
        if(resm) return a;
        else if(resn) return b;
        return mp(a.first,a.second+b.second);
    }else if(op=='n'){
        if(resn) return a;
        else if(resm) return b;
        return mp(a.first,a.second+b.second);
    }
    return mp(a.first,a.second+b.second);
}
template<typename T>void hbuild(vptt & t,vt & a,int v,int tl,int tr,char op){
    if(tl==tr){
        t[v]=mp(a[tl],1);
    }else{
        int tm=MID(tl,tr);
        hbuild(t,a,2*v+1,tl,tm,op);
        hbuild(t,a,2*v+2,tm+1,tr,op);
        t[v]=COMBINE(t[2*v+1],t[2*v+2],op);
    }
}
template<typename T>ptt hgetseg(vptt & t,int v,int tl,int tr,int l,int r,char op){
    if(l>r) return mp(IDENTITY(op),(int)0);
    else if(tl==l && r==tr) return t[v];
    int tm=MID(tl,tr);
    ptt left=hgetseg(t,2*v+1,tl,tm,l,min(r,tm),op);
    ptt right=hgetseg(t,2*v+2,tm+1,tr,max(l,tm+1),r,op);
    return COMBINE(left,right,op);
}
template<typename T>void hupdateseg(vptt & t,int v,int tl,int tr,int pos,int new_val,char op){
    if(tl==tr){
        t[v]=mp(new_val,1);
    }else{
        int tm=MID(tl,tr);
        if(pos<=tm) hupdateseg(t,2*v+1,tl,tm,pos,new_val,op);
        else hupdateseg(t,2*v+2,tm+1,tr,pos,new_val,op);
        t[v]=COMBINE(t[2*v+1],t[2*v+2],op);
    }
}
void kth_buildseg(vi & t,vi & a,int v,int tl,int tr){
    if(tl==tr){
        if(a[tl]==0) t[v]=1;
    }else{
        int tm=MID(tl,tr);
        kth_buildseg(t,a,2*v+1,tl,tm);
        kth_buildseg(t,a,2*v+2,tm+1,tr);
        t[v]=t[2*v+1]+t[2*v+2];
    }
}
void kth_updateseg(vi & t,int v,int tl,int tr,int pos,int new_val){
    //call this function only if the old_val was 0 and new_val is non_zero ......
    // or old_val was non_zero and new_val is 0
    if(tl==tr){
        if(new_val==0) t[v]++;
        else t[v]--;
    }else{
        int tm=MID(tl,tr);
        if(pos<=tm) kth_updateseg(t,2*v+1,tl,tm,pos,new_val);
        else kth_updateseg(t,2*v+2,tm+1,tr,pos,new_val);
        t[v]=t[2*v+1]+t[2*v+2];
    }
}
int kth_getseg(vi &t,int v,int tl,int tr,int l,int r){
    if(l>r) return 0;
    else if(tl==l && tr==r){
        return t[v];
    }
    int tm=MID(tl,tr);
    int left=kth_getseg(t,2*v+1,tl,tm,l,min(r,tm));
    int right=kth_getseg(t,2*v+2,tm+1,tr,max(l,tm+1),r);
    return left+right;
}
int kth_pos_findseg(vi & t,int v,int tl,int tr,int k){
    if(k>t[v]) return -1;
    else if(tl==tr) return tl;
    int tm=MID(tl,tr);
    if(t[v*2+1]>=k) return kth_pos_findseg(t,2*v+1,tl,tm,k);
    return kth_pos_findseg(t,2*v+2,tm+1,tr,k-t[v*2+1]);
}

template<typename T>void laddon_root_seg(vt & t,vt & lazy,int v,int tl,int tr,T addend,char op){
    if(op=='|'){
    	cout<<"v : "<<v<<" t[v] : "<<t[v]<<" : "<<addend<<endl;
    	if(t[v]|addend == t[v]){
    		t[v]=addend;
    		lazy[v]=addend;	
    	}else{
    		throw "-1";
    	}
    	
    }else if(op=='+' || op=='-'){
        t[v] += (tr-tl+1)*addend;
        lazy[v] += addend;

        // cout<<"adding : "<<(tr-tl+1)*addend<<" to "<<t[v]<<" at "<<v<<endl;
    }else if(op=='m' || op=='n'){
        t[v] += addend;
        lazy[v] += addend;
        // cout<<"adding : "<<addend<<" to "<<t[v]<<" at "<<v<<endl;
    }else{
        cout<<"YOU ARE APPLYING RANGE QUERIES WHICH ARE NOT VALID FOR THIS TEMPLATE"<<endl;
        cerr<<"YOU ARE APPLYING RANGE QUERIES WHICH ARE NOT VALID FOR THIS TEMPLATE"<<endl;
        exit(0);
    }

}

// template<typename T>void laddon_root_seg(vt & t,vt & lazy,int v,int tl,int tr,T addend,char op){
    
//     if(op=='+' || op=='-'){
//         t[v] += (tr-tl+1)*addend;
//         lazy[v] += addend;

//         // cout<<"adding : "<<(tr-tl+1)*addend<<" to "<<t[v]<<" at "<<v<<endl;
//     }else if(op=='m' || op=='n'){
//         t[v] += addend;
//         lazy[v] += addend;
//         // cout<<"adding : "<<addend<<" to "<<t[v]<<" at "<<v<<endl;
//     }else{
//         cout<<"YOU ARE APPLYING RANGE QUERIES WHICH ARE NOT VALID FOR THIS TEMPLATE"<<endl;
//         cerr<<"YOU ARE APPLYING RANGE QUERIES WHICH ARE NOT VALID FOR THIS TEMPLATE"<<endl;
//         exit(0);
//     }

// }
template<typename T>void lpush_adding(vt & t,vt & lazy,int v,int tl,int tr,char op){
    int tm=MID(tl,tr);
    laddon_root_seg(t,lazy,2*v+1,tl,tm,lazy[v],op);
    laddon_root_seg(t,lazy,2*v+2,tm+1,tr,lazy[v],op);
    // cout<<" pushing : "<<lazy[v]<<" at "<<v*2+1<<" and "<<v*2 + 2<<endl;
    lazy[v]=0;
}

template<typename T>void lbuildseg(vt & t,vt & a,int v,int tl,int tr,char op){
    buildseg(t,a,v,tl,tr,op);
}
template<typename T>void lupdateseg(vt & t,int v,int tl,int tr,int l,int r,T addend,char op,vt & lazy){
    if(l>r) return;
    if(l==tl && tr==r){
        laddon_root_seg(t,lazy,v,tl,tr,addend,op);
    }else{
        lpush_adding(t,lazy,v,tl,tr,op);
        int tm=MID(tl,tr);
        lupdateseg(t,2*v+1,tl,tm,l,min(r,tm),addend,op,lazy);
        lupdateseg(t,2*v+2,tm+1,tr,max(l,tm+1),r,addend,op,lazy);
        t[v]=PERFORM(t[2*v+1],t[2*v+2],op);
    }
}
template<typename T>T lgetseg(vt &t,int v,int tl,int tr,int l,int r,char op,vt &lazy){
    if(l>r) return IDENTITY(op);
    if(l<=tl && tr<=r){
        return t[v];
    }
    lpush_adding(t,lazy,v,tl,tr,op);
    int tm=MID(tl,tr);
    T left=lgetseg(t,v*2 + 1,tl,tm,l,min(r,tm),op,lazy);
    T right=lgetseg(t,v*2 + 2,tm+1,tr,max(tm+1,l),r,op,lazy);
    return PERFORM(left,right,op);
}
template<typename T>int find_prefix_seg(vt & t,int v,int tl,int tr,int x){
    if(x>t[v]) return -1;
    if(tl==tr){
        return tl;
    }
    int tm=MID(tl,tr);
    if(t[2*v+1]>=x) return find_prefix_seg(t,v*2+1,tl,tm,x);
    return find_prefix_seg(t,v*2+2,tm+1,tr,x-t[v*2+1]);
}
void perm(int a[],int n,int start=0){
    F(i,0,n) a[i]=start+i;
}
void perm(vi & a,int n,int start=0){
    F(i,0,n) a[i]=start+i;
}
void kick(int t){
    cout<<"Case #"<<t<<": ";
}
bool isspecial(char c){
    return c=='#' || c=='@' || c=='*' || c=='&';
}
bool isup(char c){
    return c>='A' && c<='Z';
}
bool isdown(char c){
    return c>='a' && c<='z';
}
bool isdigit(char c){
    return c>='0' && c<='9';
}
void reject(){
    cout<<-1<<endl;
}
string tos(unsigned long long x){
    ostringstream ostr;ostr<<x;return ostr.str();
}


void merge(int *a,int l,int mid,int r,int & ctr){
    int lz=mid-l+1,rz=r-mid;
    int left[lz];F(i,0,lz) left[i]=a[l+i];
    int right[rz];F(i,0,rz) right[i]=a[mid+i+1];
    int li=0,ri=0;
    int index=l;
    // cout<<"left : "<<endl;
    // cout<<"l : "<<l<<" to "<<"mid : "<<mid<<endl;
    // println(left,lz);

    // cout<<"right : "<<endl;
    // cout<<"mid+1 : "<<mid+1<<" to "<<"r : "<<r<<endl;
    // println(right,rz);

    while(li<lz && ri<rz){
        if(left[li]<right[ri]){
            a[index]=left[li];
            li++;
        }else{
            ctr+=lz-li;
            // cout<<"for : "<<left[li]<<" vs "<<right[ri]<<" "<<" inc "<<lz-li<<endl;
            a[index]=right[ri];
            ri++;
        }
        index++;
    }
    while(li<lz){
        a[index]=left[li];
        li++;
        index++;
    }

    while(ri<rz){
        a[index]=right[ri];
        ri++;
        index++;
    }
    // cout<<"ultimate : a "<<endl;
    // F(i,l,r+1) cout<<a[i]<<" ";
    // cout<<endl;
}
int stop=0;
void mergeSort(int *a,int l,int r,int & ctr){
    if(l>=r) return;
    // cout<<l<<" "<<r<<endl;
    int mid=(l+r)/2;
    mergeSort(a,l,mid,ctr);
    mergeSort(a,mid+1,r,ctr);
    merge(a,l,mid,r,ctr);
}

int gcdlcmdiff(int a,int b){
    return LCM(a,b)-GCD(a,b);
}
int setBits(int n){
    bitset<64> bs(n);
    return bs.count();
}
int c2i(char c){
    return c-'0';
}
bool isPrimeBig(int n){
    if(n==1) return false;
    int p=2;
    while(true){
        if(n>=p*p){
            if(n%p==0){
                return false;
                n/=p;
            }else p++;
        }else{
            return true;
            break;
        }
    }
    return false;
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
int factorial(int n){
    int mul=1;
    while(n>1){
        mul*=n;
        n--;
    }
    return mul;
}
void findAllFactors(int n,std::vector<int>& factors){

    double sqroot=sqrt(n);
    factors.push_back(1);
    if(n<=1){
        return;     
    }
    for(int i=2;i<=sqroot;i++){
        if(n%i == 0){
            factors.push_back(i);
            if(n/i != i){
                factors.push_back(n/i);
            }
        }
    }
    factors.push_back(n);
    sort(factors.begin(),factors.end());
}
template<typename T> void moveup(vvt & a){
	int n=a.size();
	vi v(n);
	F(i,0,n) v[i]=a[0][i];
	F(i,1,n){
		F(j,0,n){
			a[i-1][j]=a[i][j];
		}
	}
	F(i,0,n) a[n-1][i]=v[i];
}
template<typename T> void movedown(vvt & a){
	int n=a.size();
	vi v(n);
	F(i,0,n) v[i]=a[n-1][i];
	FND(i,n-1,1){
		F(j,0,n){
			a[i][j]=a[i-1][j];
		}
	}
	F(i,0,n) a[0][i]=v[i];
}
template<typename T> void moveleft(vvt & a){
	int n=a.size();
	vi v(n);
	F(i,0,n) v[i]=a[i][0];
	F(j,0,n-1){
		F(i,0,n){
			a[i][j]=a[i][j+1];
		}
	}
	F(i,0,n) a[i][n-1]=v[i];
}
template<typename T> void moveright(vvt & a){
	int n=a.size();
	vi v(n);
	F(i,0,n) v[i]=a[i][n-1];

	FND(j,n-1,1){
		F(i,0,n){
			a[i][j]=a[i][j-1];	
		}
	}
	F(i,0,n) a[i][0]=v[i];
}
vvc ident;
bool dir[4][4][4][4];
int L=0,R=0,U=0,D=0;
void shift(vvc & a,int itr,int & mn,int pscore=LLONG_MAX){
	int n=a.size();
	int score=0;
	F(i,0,n){
		F(j,0,n){
			if(a[i][j] != ident[i][j]) score++;
		}
	}
	// if(score>pscore) return;
	mn=min(mn,score);
	if(itr>=0){
		moveup(a);U++;
		shift(a,itr-1,mn,score);movedown(a);
		movedown(a);shift(a,itr-1,mn,score);moveup(a);
		moveleft(a);shift(a,itr-1,mn,score);moveright(a);
		moveright(a);shift(a,itr-1,mn,score);moveleft(a);
	}
	
	
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

    // void giveConnectedComps(vector<vector<int>>& comps){
    //  for(auto &pr:ump){
    //      if(pr.first==0) continue;
    //      if(pr.second > 0){
    //          comps[pr.second].push_back(pr.first);
    //      }else{
    //          comps[pr.first].push_back(pr.first);
    //      }
    //  }
    //  return;
    // }
    // void print(){
    //     for(auto &pr:ump){
    //         cout<<"{"<<pr.first<<"<="<<pr.second<<"}"<<endl;
    //     }
    // }
};
bool isPalindrome(string s){
	string rev=s;
	reverse(s.begin(),s.end());
	return rev==s;
}
bool ispal(int a,int b){
	bool res = (a/10 == b%10 && a%10 == b/10);
	if(res){
		// cout<<a<<" , "<<b<<endl;
	}
	return res;
}
bool isAllSame(string &s,char c){
    int n=s.size();
    F(i,0,n){
        if(s[i] != c) return false;
    }
    return true;
}



int prim(vvi & graph,int start){
	int n=graph.size();
	vi dist(n,LLONG_MAX);
	dist[start]=0;
	priority_queue<pii,vpii,greater<pii>> pq;
	pq.push({0,start});
	vi popped(n,false);
	while(pq.size()>0){
		pii top=pq.top();pq.pop();
		int d_v=top.first;
		int v=top.second;
		if(d_v != dist[v]) continue;
		popped[v]=true;
		F(node,0,n){
			if(node == v) continue;
			if(popped[node]==false && dist[node]>graph[v][node]){
				dist[node]=graph[v][node];
				pq.push({dist[node],node});
			}
		}
	}
	// printv(dist);
	int cost=0;
	F(i,0,n){
		cost=max(cost,dist[i]);
	}
	return cost;
}

//lcm and gcd
pair<int,int> extended_gcd(int a,int b){
	if(b==0) return{1,1};
	pair<int,int> pr=extended_gcd(b,a%b);
	return {pr.second,pr.first-(a/b)*pr.second};
}
// modulo arithmetic 
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
void permute(vi & v,int m,int n,int start,int threshold=0){
    // cout<<start<<" : "<<threshold<<endl;
    if(start>=n){
        printv(v);
        return ;
    }
    int curr=threshold+1;
    // cout<<"curr: "<<curr<<endl;
    // int rem=n-start-1;
    while(m-curr>=n-start-1){
        v[start]=curr;
        permute(v,m,n,start+1,curr);
        curr++;

    }
    // v[start]=-1;
    return ;
}
void flip(char &c){
    if(c=='1') c='0';
    else c='1';
}
class Manacher{
    string s;
    int n;
    vector<int> palCount;
    int mxIndex=-1,mx=0;
    string longestPalindrome;
public: 
    void buildString(string str){
        for(auto c:str){
            s+="$";
            s+=c;
        }
        s+="$";
    }
    Manacher(string s){
        this->n=s.size();
        this->n=2*n+1;
        this->buildString(s);
        palCount=*new vector<int>(n,0);
        this->process();
    }
    void process(){
        int iter=0;
        int start(0),end(0);
        for(int i=0;i<n;){
            while(start>0 && end<n-1 && s[start-1]==s[end+1]){
                start--;
                end++;
            }
            palCount[i]=end-start+1;
            if(end==n-1) break;
            int newCenter=end + ((i%2 == 0)?(1):(0));
            for(int j=i+1;j<=end;j++){
                if(s[i]=='$') continue;
                palCount[j]=min(palCount[i-(j-i)],2*(end-j)+1);
                if(j+palCount[i-(j-i)]/2 == end){
                    newCenter=j;
                    break;
                }
            }
            i=newCenter;
            end=i+palCount[i]/2;
            start=i-palCount[i]/2;
        }
        for(int i=0;i<n;i++){
            if(palCount[i] >mx){
                mx=palCount[i];
                mxIndex=i;
            }
        }
        longestPalindrome=s.substr(mxIndex-mx/2,mx);
        string dummy=longestPalindrome;
        longestPalindrome="";
        for(auto c:dummy){
            if(c!='$') longestPalindrome+=c;
        }
    }
    void print(){
        for(int i=0;i<n;i++){
            cout<<i<<" : "<<palCount[i]<<endl;
        }
    }
    int getLen(){
        return mx/2;
    }
    string getPal(){
        return longestPalindrome;
    }
    string getString(){
        return s;
    }
    vector<int> manacher_odd(string& str) {
        int n = s.size();
        string s = "#" + s + "^";
        vector<int> p(n + 2);
        for(int i = 1; i <= n; i++) {
            while(s[i - p[i]] == s[i + p[i]]) {
                p[i]++;
            }
        }
        return vector<int>(begin(p) + 1, end(p) - 1);
    }
    int ps(){
        vector<int> p=manacher_odd(s);
        // for(int i=0;i<n;i++){
        //     cout<<s[i]<<" : "<<p[i]<<endl;
        // }
        // cout<<endl;
        for(int i=1;i<n;i+=2){
            int leftlen=i+1;
            int leftmid=(i+1)/2;
            int rightmid=(i+1+n-1)/2;
            int rightlen=n-1-(i+1)+1;
            // cout<<leftlen<<" l :"<<leftmid<<": l "<<2*(p[leftmid]-1)<<endl;
            // cout<<rightlen<<" r :"<<rightmid<<": r "<<2*p[rightmid]-1<<endl;
            if(leftlen==2*(p[leftmid]-1) && (rightlen==2*p[rightmid]-1)){
                return i;
            }
        }
        return n;
    }
};

string buildString(string& str){
    string s;
    for(auto c:str){
        s+="$";
        s+=c;
    }
    s+="$";
    return s;
}
void manacher_odd(vector<int>& p,string s){
    int n = s.size();
    s = "#" + s + "^";
    for(int i = 1; i <= n; i++) {
        while(s[i - p[i]] == s[i + p[i]]) {
            p[i]++;
        }
    }
}
void printmap(map<int,int>& v1){
    for(auto &pr:v1){
        cout<<pr.first<<","<<pr.second<<" } ";
    }
    cout<<endl;
}

string intToString(int n){
    ostringstream ostr;
    ostr<<n;
    return ostr.str();
}


void solve(int t){
    //shree ganeshay namah  
    int n;
    read(n);
    int num=factorial(n-1);
    num*=2;
    num/=n;
    println(num);

    // kick(t);
    
    // write your answer here
    
    //complete your answer here
    // println();
}   

    

inline bool isTakeTestCase(){

    // return true;
    return false;
}
signed main(){
    #ifndef ONLINE_JUDGE
        freopen("input.txt", "r", stdin);
        freopen("error.txt", "w", stderr);
        freopen("output.txt", "w", stdout);
    #endif
    FASTIO;
    BOOLALPHA;
    int t=1;
    if(isTakeTestCase()) read(t);
    F(i,1,t+1){
        solve(i);
    }
    // cerr<<"time taken : "<<(float)clock()/CLOCKS_PER_SEC<<" secs"<<endl;
    return 0;
}   


