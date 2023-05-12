#include<bits/stdc++.h>
#define int long long
#define endl "\n"
#define pii pair<int,int>
using namespace std;
//stringToInt
int stringToInt(const string &s){
	stringstream om(s);
	int num=-1;
	om>>num;
	return num;
}
// check timeout
void checkTimeout(){
	double tm=(float)clock()/CLOCKS_PER_SEC;
	if(tm>=2){
		cerr<<"Time limit exeeded"<<endl;
		exit(0);
	}
}
//factors 
void findAllFactors(int n,std::vector<int>& factors){
	double sqroot=sqrt(n);
	factors.push_back(1);
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
//lcm and gcd
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
//printing modules
void print(int num){
	cout<<num<<endl;
}
void print(int *arr,int start,int end){
	for(int i=start;i<=end;i++){
		cout<<arr[i]<<" ";
	}cout<<endl;
}
void print(int *arr,int n){
	for(int i=0;i<n;i++){
		cout<<arr[i]<<" ";
	}cout<<endl;
}
void print(vector<pair<int,int>>& v){
	for(auto &pr:v){
		cout<<"{"<<pr.first<<","<<pr.second<<"}"<<endl;
	}
	cout<<endl;
}
void print(std::vector<int>& v){
	for(auto &num:v) cout<<num<<" ";cout<<endl;
}
void print(std::vector<string>& v){
	for(auto &num:v) cout<<num<<" ";cout<<endl;
}
void print(std::vector<std::vector<int>>& v,int n){
	for(int i=n-1;i>=0;i--){
		print(v[i]);
	}
}
void print(bool b){
	if(b) cout<<"YES";
	else cout<<"NO";
	cout<<endl;
}
void print(pair<int,int>& pr){
	cout<<"{"<<pr.first<<","<<pr.second<<"} ";
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
int chineseRem(int arr[],int rem[],int n){
	int prod=1,res=0;
	for(int i=0;i<n;i++) prod*=arr[i];
	for(int i=0;i<n;i++){
		int restProd=prod/arr[i];
		res+=(rem[i]*modInv(restProd,arr[i])*(restProd));
	}
	return (res%prod);
}
// fenwick tree
class fenwickTree{
	vector<int> BIT;
	int n;
	public : 
	fenwickTree(int n){
		this->n=n;
		BIT=*new vector<int>(n,0);
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
		this->n=n;
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
};
	
//segment tree
class segmentTree{
	vector<int> segTree;
	int *arr;int n;
	bool isVectorContainer=false;
	public: 
	segmentTree(int *arr,int n){
		this->arr=arr;
		this->n=n;
		int size=pow(2,ceil(log2(2*n-1)));
		segTree.resize(size);
		createSegTree(0,0,n-1);
	}
	segmentTree(vector<int> &v){
		isVectorContainer=true;
		n=v.size();
		this->arr=(int *)malloc(n*sizeof(int));
		for(int i=0;i<n;i++){
			arr[i]=v[i];
		}
		int size=pow(2,ceil(log2(2*n-1)));
		segTree.resize(size);
		createSegTree(0,0,n-1);
	}
	int createSegTree(int si,int l,int r){
		if(l==r){	
			segTree[si]=arr[l];
			return arr[l];
		}
		int mid=(l+r)/2;
		segTree[si]=createSegTree(2*si + 1,l,mid)+createSegTree(2*si + 2,mid+1,r);
		return segTree[si];
	}
	int getRangeSum(int sl,int sr,int l,int r,int si){
		// cout<<sl<<" "<<sr<<endl;
		if(sl>=l && sr<=r){
			return segTree[si];
		}
		if(sl>r || sr<l){
			return 0;
		}
		int mid=(sl+sr)/2;
		return getRangeSum(sl,mid,l,r,2*si+1)+getRangeSum(mid+1,sr,l,r,2*si+2);
	}
	int getRangeSum(int l,int r){
		return this->getRangeSum(0,n-1,l,r,0);
	}

	void updateSegTree(int si,int sl,int sr,int pos,int diff){
		if(sl>pos || sr<pos) return;
		segTree[si]+=diff;
		if(sl != sr){
			int mid((sl+sr)/2);
			updateSegTree(2*si+1,sl,mid,pos,diff);
			updateSegTree(2*si+2,mid+1,sr,pos,diff);
		}
	}
	void update(int pos,int x){
		int diff=x-arr[pos];
		return updateSegTree(0,0,n-1,pos,diff);
	}
	~segmentTree(){
		if(isVectorContainer){
			free(arr);
		}
	}
};
// sqroot decomposition

class sqrtDecomp{
	int *arr;
	int n;
	int len;
	vector<int> decomp;
	public :
	sqrtDecomp(int *arr,int n){
		this->n=n;
		this->arr=arr;
		len=sqrt(n)+1;
		decomp=*new vector<int>(len,0);
		for(int i=0;i<n;i++){
			decomp[i/len]+=arr[i];
		}
	}
	sqrtDecomp(vector<int>& v){
		this->n=n;
		arr=(int *)malloc(n*sizeof(int));
		for(int i=0;i<n;i++) arr[i]=v[i];
		len=sqrt(n)+1;
		decomp=*new vector<int>(len,0);
		for(int i=0;i<n;i++){
			decomp[i/len]+=arr[i];
		}
	}
	int getRangeSum(int l,int r){
		int sum=0;
		for(int i=l;i<=r;){
			if(i%len==0 && i+len-1<=r){
				sum+=decomp[i/len];
				i+=len;
			}else{ 
				sum+=arr[i];
				i++;
			}
		}
		return sum;
	}
};
// disjointSet
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
    bool prefered_union(int v,int u){
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

    // void giveConnectedComps(vector<vector<int>>& comps){
    // 	for(auto &pr:ump){
    // 		if(pr.first==0) continue;
    // 		if(pr.second > 0){
    // 			comps[pr.second].push_back(pr.first);
    // 		}else{
    // 			comps[pr.first].push_back(pr.first);
    // 		}
    // 	}
    // 	return;
    // }
    // void print(){
    //     for(auto &pr:ump){
    //         cout<<"{"<<pr.first<<"<="<<pr.second<<"}"<<endl;
    //     }
    // }
};
//lis
int lis(int *v,int n){
	vector<int> seq;
	for(int i=0;i<n;i++){
		int num=v[i];
		auto found=upper_bound(seq.begin(), seq.end(),num);
		if(found==seq.end()) seq.push_back(num);
		else *found=num;
	}
	return seq.size();
}
int lis(vector<int>&v){
	int n=v.size();
	vector<int> seq;
	for(auto num:v){
		auto found=upper_bound(seq.begin(), seq.end(),num);
		if(found==seq.end()) seq.push_back(num);
		else *found=num;
	}
	return seq.size();
}
//lis return type list
void lis(int *v,int n,vector<int>&seq){
	for(int i=0;i<n;i++){
		int num=v[i];
		auto found=upper_bound(seq.begin(), seq.end(),num);
		if(found==seq.end()) seq.push_back(num);
		else *found=num;
	}
	return ;
}
void lis(vector<int>&v,vector<int>& seq){
	int n=v.size();
	for(auto num:v){
		auto found=upper_bound(seq.begin(), seq.end(),num);
		if(found==seq.end()) seq.push_back(num);
		else *found=num;
	}
	return;
}

// scanning modules
void scan(int *arr,int n){
	for(int i=0;i<n;i++) cin>>arr[i];
}
void scan(vector<int>& v,int n){
	for(int i=0;i<n;i++) cin>>v[i];
}
void scan(int *arr,int n,vector<int>& hash){
	for(int i=0;i<n;i++) {cin>>arr[i];hash[arr[i]]=i;}
}
void scan(vector<int>& v,int n,vector<int>& hash){
	for(int i=0;i<n;i++) {cin>>v[i];hash[v[i]]=i;}
}
void scan(int *arr,int n,unordered_map<int,int>& hash){
	for(int i=0;i<n;i++) {cin>>arr[i];hash[arr[i]]=i;}
}
void scan(vector<int>& v,int n,unordered_map<int,int>& hash){
	for(int i=0;i<n;i++) {cin>>v[i];hash[v[i]]=i;}
}
// primeDivisors return type number
int primeFactorsBig(int n){
	unordered_set<int> uns;
	int p=2;
	while(true){
		if(n>=p*p){
			if(n%p==0){
				uns.insert(p);
				n/=p;
			}else p++;
		}else{
			uns.insert(n);
			break;
		}
	}
	return uns.size();
}
// primeDivisors with return type vector

void primeFactorsBig(int n,map<int,int>& mp){
	int p=2;
	while(true){
		if(n>=p*p){
			if(n%p==0){
				mp[p]++;
				n/=p;
			}else p++;
		}else{
			mp[n]++;
			break;
		}
	}
	return;
}
void primeFactorsBig(int n,vector<int>& v){
	unordered_set<int> uns;
	int p=2;
	while(true){
		if(n>=p*p){
			if(n%p==0){
				uns.insert(p);
				n/=p;
			}else p++;
		}else{
			uns.insert(n);
			break;
		}
	}
	v.resize(uns.size());
	int len=0;
	for(auto num:uns) v[len++]=num;
	sort(v.begin(), v.end());
	return;
}
// isPrime
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
// sieve of erathosthens for prime
const int N=1e6+10;
vector<int> highestPrime(1e6+10,0);
vector<int> lowestPrime(1e6,0);
vector<int> primes;
// vector<vector<int>> factorsOf(N);
bitset <N> nonPrimeSet;
void seive(){
	nonPrimeSet[0]=nonPrimeSet[1]=1;
	
	for(int num=2;num*num<=N;num++){
		if(0==nonPrimeSet[num]){
			for(int j=num*num;j<=N;j+=num){
				nonPrimeSet[j]=1;
			}
		}
	}
	
}
void seiveWithAllPrimes(){
	nonPrimeSet[0]=nonPrimeSet[1]=1;
	
	for(int num=2;num*num<=N;num++){
		if(0==nonPrimeSet[num]){
			for(int j=num*num;j<=N;j+=num){
				nonPrimeSet[j]=1;
			}
		}
	}
	for(int num=2;num<=N;num++){
		if(0==nonPrimeSet[num]) primes.push_back(num);
	}
}
void seiveWithHPLP(){
	nonPrimeSet[0]=nonPrimeSet[1]=1;
	for(int num=2;num*num<=N;num++){
		if(0==nonPrimeSet[num]){
			for(int j=num*num;j<=N;j+=num){
				nonPrimeSet[j]=1;
				if(lowestPrime[j]==0) lowestPrime[j]=num;
				highestPrime[j]=num;
			}
			highestPrime[num]=lowestPrime[num]=num;
		}
	}
	
}
// void seiveWithAllFactors(){
// 	nonPrimeSet[0]=nonPrimeSet[1]=1;
	
// 	for(int num=2;num<=N;num++){
// 		factorsOf[num].push_back(1);
// 		if(0==nonPrimeSet[num]){
// 			for(int j=num*num;j<=N;j+=num){
// 				factorsOf[j].push_back(num);
// 				nonPrimeSet[j]=1;
// 				if(lowestPrime[j]==0) lowestPrime[j]=num;
// 				highestPrime[j]=num;
// 			}primes.push_back(num);
// 			highestPrime[num]=lowestPrime[num]=num;
// 		}else{
// 			for(int j=num+num;j<=N;j+=num){
// 				factorsOf[j].push_back(num);
// 			}
// 		}
// 		factorsOf[num].push_back(num);
// 	}
// }

void segmentedSeive(int l,int r,vector<int>& segPrimes){
	int limit=ceil(sqrt(r));
	int sz=r-l+1;
	vector<bool> bs(sz,0);
	for(auto primeNum:primes){
		if(primeNum<=limit){
			int firstMultiple=(l/primeNum)*primeNum;
			if(firstMultiple<l) firstMultiple+=l;
			for(int num=max(firstMultiple,primeNum*primeNum);num<=r;num+=primeNum){
				bs[num-l]=1;
			}
		}
	}
	for(int i=0;i<sz;i++){
		if(bs[i]==0) segPrimes.push_back(i+l);
	}
}
int rangePrimes(int l,int r){
	if(r<=1e6){
		int ctr=0;
		for(int i=l;i<=r;i++){
			if(nonPrimeSet[i]==0) ctr++;
		}
		return ctr;
	}else{
		vector<int> segPrimes;
		segmentedSeive(l,r,segPrimes);
		return segPrimes.size();
	}
}
void rangePrimes(int l,int r,vector<int>& segPrimes){
	if(r<=1e6){
		for(int i=l;i<=r;i++){
			if(nonPrimeSet[i]==0) segPrimes.push_back(i);
		}
		return; 
	}
	return segmentedSeive(l,r,segPrimes);
}
bool isPrime(int n){
	if(n>1e6) return isPrimeBig(n);
	return 0==nonPrimeSet[n];
}
void primeFactors(int n,vector<int>&v){
	if(n<2) return;
	if(n>1e6) return primeFactorsBig(n,v);
	while(n>1){
		int prime_factor=highestPrime[n];
		while(n%prime_factor==0){
			n/=prime_factor;
			
		}
		v.push_back(prime_factor);
	}
}
void primeFactors(int n,map<int,int>& mp){
	if(n<2) return;
	if(n>1e6) return primeFactorsBig(n,mp);
	while(n>1){
		int prime_factor=highestPrime[n];
		while(n%prime_factor==0){
			n/=prime_factor;
			mp[prime_factor]++;
		}
	}
}

int primeFactors(int n){
	if(n<2) return 0;
	if(n>1e6) return primeFactorsBig(n);
	int noOfPrimeFactors=0;
	while(n>1){
		int prime_factor=highestPrime[n];
		while(n%prime_factor==0){
			n/=prime_factor;
			noOfPrimeFactors++;
		}
	}
	return noOfPrimeFactors;
}
// roundOf
int roundOf(int n){
	return (int)pow(2,floor(log2(n)));
}
// string and pattern mathcing
// string -- // z algorithm
void createZ(string s,int z[]){
	int n=s.size();
	int l,r,k;
	l=r=0;
	z[0]=0;
	for(int i=1;i<n;i++){
		if(i>r){
			l=r=i;
			while(r<n && s[r]==s[r-l]){
				r++;
			}
			z[i]=r-l;
			r--;
		}else{
			k=i-l;
			if(z[k]<r-i+1){
				z[i]=z[k];
			}else{
				l=i;
				while(r<n && s[r-l]==s[r]){
					r++;
				}
				z[i]=r-l;
				r--;
			}
		}
	}
}
void zSearch(string text,string pattern,vector<int>& match){
	string concat=pattern+"$"+text;
	int sz=concat.length();
	int psize=pattern.size();
	int z[sz];
	createZ(concat,z);
	for(int i=0;i<sz;i++){
		if(z[i]==psize){
			match.push_back(i-psize-1);
		}
	}
	return;
}

bool stringCompare(string &s,int ss,string &r,int rs,int len){
	if(ss+len>s.size() || rs+len>r.size()) return false;
	for(int i=0;i<len;i++,ss++,rs++){
		if(s[ss]!=r[rs]) return false;
	}
	return true;
}
void rabin(string s,string pattern,vector<int>&match){
	int sz=s.size();
	int pz=pattern.size();
	if(pz>sz) return;
	int primeNum=3;
	int hashVal=0;
	int patternHash=0;
	for(int i=0;i<pz;i++){
		patternHash+=((int)(pattern[i]-97 + 1))*pow(primeNum,i);
	}
	
	// cout<<"patternHash :"<<patternHash<<endl;
	for(int i=0;i<pz;i++){
		hashVal+=((int)(s[i]-97 + 1))*pow(primeNum,i);
	}
	if(hashVal==patternHash) match.push_back(0);
	for(int i=pz;i<sz;i++){
		
		int k=i-pz;
		hashVal-=(int)(s[k]-97+1);
		hashVal/=3;
		hashVal+=((int)(s[i]-97+1))*pow(primeNum,pz-1);
		if(hashVal==patternHash && (stringCompare(s,k+1,pattern,0,pz))) match.push_back(k+1);
	}
}
void prefix_function(string s,vector<int>& pf){
	int n=s.size();
	pf.resize(n);
	pf[0]=0;
	for(int i=1;i<n;i++){
		int j=pf[i-1];
		while(j>0 && s[i]!=s[j]){
			j=pf[j-1];
		}
		if(s[i]==s[j]){
			j++;
		}
		pf[i]=j;
	}
	// Time complexity : O(n)
}
void kmp(string s,string pattern,vector<int>&match){
	int pz=pattern.size();
	int pos(-1),i(0),j(0);
	vector<int> pf;
	prefix_function(pattern,pf);
	for(auto num:pf) cout<<num<<" ";cout<<endl;
	while(i<s.size()){
		if(s[i]==pattern[j]){
			j++;
			i++;
		}else{
			if(j!=0){
				j=pf[j-1];
			}else i++;
		}
		if(j==pattern.size()){
			match.push_back(i-pz);
		}
	}
}
void reject(){
	cout<<-1<<endl;
	return;
}
void freqscan(int b[],int n,unordered_map<int,int>& hash){
	for(int i=0;i<n;i++){
		cin>>b[i];
		hash[b[i]]++;
	}
}
class sparseTable{
	int *arr;
	int n;
	vector<vector<int>> table;
	int col=0;
	public: 
	void buildTable(){
		for(int i=0;i<n;i++) table[i][0]=arr[i];
		for(int j=1;j<col;j++){
			for(int i=0;i+(1<<j)-1<n;i++){
				table[i][j]=min(table[i][j-1],table[i+(1<<(j-1))][j-1]);
			}
		}
	}
	sparseTable(int *arr,int n){
		this->arr=arr;
		this->n=n;
		col=1+log2(n);
		table=*new vector<vector<int>>(n,*new vector<int>(col));
		this->buildTable();
	}
	int getRangeMin(int l,int r){
		int diff=r-l+1;
		int j=log2(diff);
		return min(table[l][j],table[r-(1<<j)+1][j]);
	}
	void print(){
		for(int i=0;i<n;i++){
			for(int j=0;j<col;j++){
				cout<<table[i][j]<<" ";
			}cout<<endl;
		}
	}
};
class Query{
public: 
	int index,l,r,sum;
};
class mosAlgo{
public: 
	
	int *arr;
	int n;
	int len;
	// vector<Query> que;
	mosAlgo(int *arr,int n){
		this->arr=arr;
		this->n=n;
		this->len=sqrt(n);
	}
	void process(vector<Query>& que,vector<int>& v){
		int q=que.size();
		sort(que.begin(), que.end(),[&](Query&a,Query&b){
			if((a.l)/len == (b.l)/len){
				return a.r>b.r;
			}
			return a.l/len<b.l/len;
		});
		int currL=0,currR=-1,currSum=0;
		for(int i=0;i<q;i++){
			Query &query=que[i];
			while(currL<query.l){
				currSum-=arr[currL];
				currL++;
			}
			while(currL>query.l){
				currL--;
				currSum+=arr[currL];
			}
			while(currR<query.r){
				currR++;
				currSum+=arr[currR];
			}
			while(currR>query.r){
				currSum-=arr[currR];
				currR--;
			}
			query.sum=currSum;
			v[query.index]=currSum;
		}
	}
};
// longest palindromic substring , manachers' algo
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

};
bool isPalindrome(string s){
	string rev=s;
	reverse(s.begin(), s.end());
	return s==rev;
}

class EulerTotient{
	public : 
	int n;
	vector<int> totient;
	EulerTotient(int N){
		this->n=N+1;
		totient.resize(n);
		for(int i=0;i<n;i++){
			totient[i]=i;
		}
		for(int i=2;i<n;i++){
			if(totient[i]==i){
				for(int j=2*i;j<n;j+=i){
					totient[j]*=(i-1);
					totient[j]/=i;
				}
				totient[i]=i-1;
			}
		}
	}
	void print(){
		for(auto num:totient) cout<<num<<" ";cout<<endl;
	}
	inline int get(int index){
		return totient.at(index);
	}
};
class MatrixExp{
	public : 
	int n,row,col;
	vector<vector<int>>& mat;
	vector<vector<int>> resultMat;
	// function to multiply matrices 
	vector<vector<int>> matrixMultiply(vector<vector<int>>& mat1,vector<vector<int>>& mat2){
		if(mat1[0].size() != mat2.size()){
			cout<<"invalid matrix matrixMultiply"<<endl;
			exit(0);
		}
		int myrow=(int)mat1.size(),mycol=(int)mat2[0].size(),comm=(int)mat1[0].size();
		vector<vector<int>> mulMat((int)mat1.size(),vector<int>((int)mat2[0].size()));
		for(int i=0;i<myrow;i++){
			for(int j=0;j<mycol;j++){
				mulMat[i][j]=0;
				for(int k=0;k<comm;k++){
					mulMat[i][j]+=mat1[i][k]*mat2[k][j];
				}
			}
		}
		// cout<<"mat1 : "<<endl;printMatrix(mat1);
		// cout<<"mat2 : "<<endl;printMatrix(mat2);
		// cout<<"res : "<<endl;printMatrix(mulMat);
		return mulMat;
	}
	// function to make identitiy matrix 
	void makeIdentityMatrix(vector<vector<int>> &identityMat){
		identityMat.resize(row);
		for(int i=0;i<row;i++){
			identityMat[i]=*new vector<int>(row,0);
			identityMat[i][i]=1;
		}
		return;
	}
	// function to exponentiate matrix 
	vector<vector<int>> exponentiate(int power){
		if(power==1){
			return mat;
		}
		vector<vector<int>> mymat;
		if(power==0){
			this->makeIdentityMatrix(mymat);

			return mymat;
		}
		mymat=this->exponentiate(power/2);
		vector<vector<int>> ansmat=matrixMultiply(mymat,mymat);
		if(power & 1){
			ansmat=matrixMultiply(ansmat,mat);
		}
		// cout<<" power : "<<power<<endl;
		// printMatrix(ansmat);
		return ansmat;
	}
	// constructor
	MatrixExp(int N,vector<vector<int>> &vmat):n(N),mat(vmat){
		row=mat.size();
		col=mat[0].size();
		resultMat=this->exponentiate(n);
	}
	// overloaded constructor
	MatrixExp(int N):n(N),mat(*new vector<vector<int>>{{1,1},{1,0}}){
		row=mat.size();
		col=mat[0].size();
		resultMat=this->exponentiate(n);
	}
	// getter for resultmatrix
	vector<vector<int>>& getResultMatrix(){
		return this->resultMat;
	}
	// method to print result mat
	void printMatrix(vector<vector<int>>& vmatrix){
		for(auto &rowv:vmatrix){
			for(auto elem:rowv) cout<<elem<<" ";cout<<endl;
		}
	}
	void print(){
		for(auto &rowv:resultMat){
			for(auto elem:rowv) cout<<elem<<" ";cout<<endl;
		}
	}
};
class Fibonacci{
	public :
	int n;
	vector<vector<int>> mymat{{1,1},{1,0}};
	MatrixExp &me;
	Fibonacci(int n):n(n),me(*new MatrixExp(n,mymat)){}
	int get(){
		if(n==0) return 0;
		vector<vector<int>>& fibMatrix=me.getResultMatrix();
		return fibMatrix[0][0];
	}
};

class NCR{
	public : 
	int mod=-1;
	int n,r,res=1;
	void computeNcr(){
		if(r>n){
			res=0;
			return;
		}
		for(int i=0;i<r;i++){
			res*=(n-i);
			res/=(i+1);
		}
	}
	void computeNcrMod(){
		if(r>n){
			res=0;
			return;
		}
		for(int i=0;i<r;i++){
			res=modMul(res,n-i,mod);
			res=modDiv(res,i+1,mod);
		}
	}
	NCR(int n,int r):n(n),r(r){
		if(r>n-r) r=n-r;
		this->computeNcr();
	}
	NCR(int n,int r,int mod):n(n),r(r),mod(mod){
		if(r>n-r) r=n-r;
		this->computeNcrMod();
	}
	int get(){
		return res;
	}
};

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
class centroidDecomp{
public:
	int no_of_vertices;
	vector<vector<int>> tree;
	vector<vector<int>> centroidTree;
	vector<int> subtreeSizeOf;
	vector<bool> visited;
	vector<bool> isCentroid;
	int stop=0;
	centroidDecomp(int N){
		this->no_of_vertices=N+1;
		tree.resize(no_of_vertices);
		subtreeSizeOf.resize(no_of_vertices);
		centroidTree.resize(no_of_vertices);
		visited.resize(no_of_vertices);
		isCentroid=*new vector<bool>(no_of_vertices,false);
	}
	
	void DFS(int src,int& N){
		// cout<<"dfs at : "<<src<<endl;
		if(++stop>=100) exit(0);
		visited[src]=true;
		N += 1;
		subtreeSizeOf[src]=1;
		for(auto childNode:tree[src]){
			if(!visited[childNode] && !isCentroid[childNode]){
				DFS(childNode,N);
				subtreeSizeOf[src]+=subtreeSizeOf[childNode];
			}
		}
	}
	int getCentroidUtil(int src,int N){
		bool is_this_node_centroid=true;
		visited[src]=true;
		int heaviest_child=0;
		for(auto childNode:tree[src]){
			if(!visited[childNode] && !isCentroid[childNode]){
				if(subtreeSizeOf[childNode]>N/2){
					is_this_node_centroid=false;
				}
				if(heaviest_child==0 || subtreeSizeOf[childNode] > subtreeSizeOf[heaviest_child]){
					heaviest_child=childNode;
				}
			}
		}
		if(is_this_node_centroid && (N-subtreeSizeOf[src] <= N/2)){
			return src;
		}
		return getCentroidUtil(heaviest_child,N);
	}
	int getCentroid(int src){
		this->clearVisitedAndSubtreeSizeOf();
		int N=0;
		DFS(src,N);
		this->clearVisited();
		int centroid=getCentroidUtil(src,N);
		isCentroid[centroid]=true;
		return centroid;
	}
	int decompose(int root){
		int currCentroidNode=getCentroid(root);
		for(auto childNodeOfCentroid:tree[currCentroidNode]){
			if(!isCentroid[childNodeOfCentroid]){
				int subCentroidNode=this->decompose(childNodeOfCentroid);
				centroidTree[currCentroidNode].push_back(subCentroidNode);
				centroidTree[subCentroidNode].push_back(currCentroidNode);
			}
		}
		return currCentroidNode;
	}
	void addEdge (int u,int v){
		tree[u].push_back(v);
		tree[v].push_back(u);
	}
	void clearVisitedAndSubtreeSizeOf(){
		for(int i=0;i<no_of_vertices;i++){
			visited[i]=false;
			subtreeSizeOf[i]=0;
		}
	}
	void clearVisited(){
		for(int i=0;i<no_of_vertices;i++){
			visited[i]=false;
		}
	}
	void print(){
		for(int i=1;i<no_of_vertices;i++){
			cout<<i<<"< : >";
			for(auto node:centroidTree[i]) cout<<node<<" ";cout<<endl;
		}
	}
};
class Trie{
public:

	class TrieNode{
	public:
		bool end=false;
		vector<TrieNode*> nextNodeOf{*new vector<TrieNode*>(26,NULL)};
	};
	TrieNode* trieRoot=NULL;
	Trie(){
		trieRoot=new TrieNode();
	}
	void insert(const string& word){
		TrieNode* currNode=trieRoot;
		for(auto ch:word){
			if(NULL == (currNode->nextNodeOf[ch-'a'])){
				currNode->nextNodeOf[ch-'a'] = new TrieNode();
			}
			currNode=currNode->nextNodeOf[ch-'a'];
		}
		currNode->end=true;
	}
	bool search(const string& key){
		TrieNode* currNode=trieRoot;
		for(auto ch:key){
			if(NULL == (currNode->nextNodeOf[ch-'a'])){
				return false;
			}
			currNode=currNode->nextNodeOf[ch-'a'];
		}
		return currNode->end;
	}
	bool searchPrefix(const string& key){
		TrieNode* currNode=trieRoot;
		for(auto ch:key){
			if(NULL == (currNode->nextNodeOf[ch-'a'])){
				return false;
			}
			currNode=currNode->nextNodeOf[ch-'a'];
		}
		return true;
	}
};

class Graph{
	public : 
	vector<vector<int>> graph;
	vector<vector<int>> solutionColorVectors;
	vector<int> colorOf;
	int n;
	int no_of_colors=0;
	Graph(int n){
		graph.resize(n+1);
		colorOf.assign(n+1,0);
		this->n=n;
	}
	void set_no_of_colors(int m){
		this->no_of_colors=m;
	}
	void addEdge(int u,int v){
		graph[u].push_back(v);
	}
	void printGraph(){
		for(int i=1;i<=n;i++){
			cout<<i<<" : ";
			for(auto neb:graph[i]){
				cout<<neb<<" ";
			}cout<<endl;
		}
	}
	void mcolor(int start){
		if(start>n){
			solutionColorVectors.push_back(colorOf);
			return;
		}
		vector<bool> isValidColor(no_of_colors+1,true);
		for(auto node:graph[start]){
			isValidColor[colorOf[node]]=false;
		}
		for(int i=1;i<=no_of_colors;i++){
			if(isValidColor[i]){
				colorOf[start]=i;
				this->mcolor(start+1);
			}
		}
		colorOf[start]=0;
		return;
	}
	void printSolutionColorVectors(){
		for(auto & colorVector:solutionColorVectors){
			for(int i=1;i<=n;i++){
				cout<<colorVector[i]<<" ";
			}
			cout<<endl;
		}
	}

};
inline int convert(int i,int j,int n){
	return (i*n + j);
}
int fact[16];
unordered_map<int,int> memo;
int setBits(int n){
	bitset<40> bs(n);
	return bs.count();
}
NCRefficient* ncr;
void init(){
	int mod=1e9 + 7;
	ncr=new NCRefficient(N,mod);
}
void segBuild(vector<int>&seg,vector<int>&des,int n){
	int domain,start,bit;
	domain=n;start=domain-1;bit=1;
    while(domain>0){
	    
    	for(int index=start;index<start+domain;index++){
    		if(bit==1){
    			seg[index]=(seg[(2*index) + 1] | seg[(2*index) + 2]);
    		}else{
    			seg[index]=(seg[(2*index) + 1] xor seg[(2*index) + 2]);
    		}
    		des[index]=bit;
    	}

        bit=(bit^1);
    	domain=domain/2;start=domain-1;
    }
}
void segUpdate(vector<int>&seg,vector<int>&des,int pos,int val){
	int domain=pow(2,(1+floor(log2(pos))));pos-=1;
    int mypos=pos+ seg.size()/2;
    seg[mypos]=val;
    while( mypos>0){
    	mypos=(mypos-1)/2;
        if(des[mypos]==1) 
            seg[mypos]=(seg[(2*mypos) + 1] | seg[(2*mypos) + 2]);
        else
            seg[mypos]=(seg[(2*mypos) + 1] xor seg[(2*mypos) + 2]);

    }
        
}

void dfs(vector<vector<int>>& tree,vector<int>& score,vector<int>& mex,int start,int par,fenwickTree& fs,vector<int>& recStack){
	int n=tree.size();
	int l=0,r=n,missing=0;
	bool updated=false;
	if(recStack[score[start]] != 1){
		fs.update(score[start],1);
		recStack[score[start]]=1;	
		updated=true;
	} 
	while(l<r){
		// cout<<l<<" "<<r<<endl;
		int mid=(l+r)/2;
		// cout<<" mid : "<<fs.get(mid)<<endl;
		if(fs.get(mid)==mid+1) l=mid+1;
		else{ r=mid;missing=mid;}
	}
	// cout<<start<<" missing : "<<missing<<endl;
	mex[start]=missing;
	for(auto node : tree[start]){
		if(node != par) dfs(tree,score,mex,node,start,fs,recStack);
	}
	if(updated){
		fs.update(score[start],-1);
		recStack[score[start]]=0;
	}
}
int myfun(int n){
	return (n*(n+1)/2 - 1);
}
vector<int> powers;
int powerNumbers(int n)
{
    // v is going to store all power numbers
    vector<int>& v=powers;
    v.push_back(1);
 
    // Traverse through all base numbers and
    // compute all their powers smaller than
    // or equal to n.
    typedef long long ll;
    for (ll i = 2; i * i <= n; i++) {
        ll j = i * i;
        v.push_back(j);
        while (j * i <= n) {
            v.push_back(j * i);
            j = j * i;
        }
    }
 
    // Remove all duplicates
    sort(v.begin(), v.end());
    v.erase(unique(v.begin(), v.end()), v.end());
 	
    return v.size();
}
int doit(int x,int c,int par){
	if(c==1) return 1;
	vector<int> v;
	findAllFactors(x,v);
	int mod=(1e10+9);
	int mn=mod;
	// print(v);
	unordered_map<int,int> ump;
	int num=x;
	while(num%2==0){
		num/=2;
		ump[2]++;
	}
	for(int i=3;num>1;i+=2){
		while(num%i==0){
			num/=i;
			ump[i]++;
		}
	}
    int mem=1;
	for(auto &pr:ump){
		// cout<<pr.first<<" ^ "<<pr.second<<endl;
		
		mem*=pow(pr.first,min(pr.second%c,c-pr.second%c));
	}
	// if(mem<par)
	// return min(mem,doit(mem,c,mem));
	return mem;
}
// map<pair<int,int>,int> mp;
const int MOD1=1e9+7;
int dp(int n,int m,int k){
	if(n==1 or k==1) return m;
	// if(mp.count({n,k})) return mp[{n,k}];
	int ctr=0;
	for(int i=1;i<n;i++){
		ctr=modAdd(ctr,dp(n-i,m,k-1),MOD1);
	}
	ctr=modMul(ctr,m,MOD1);
	// mp[{n,k}]=ctr;
	return ctr;
}
void solve(int t){
	int n,m,k;cin>>n>>m>>k;
	int ans=dp(n,m,k);
	cout<<ans<<endl;
}
signed main(){     
	
	ios_base::sync_with_stdio(false);
    cin.tie(NULL);
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("error.txt", "w", stderr);
    freopen("output.txt", "w", stdout);
#endif
	// seive();
	// seiveWithHPLP();
	// seiveWithAllFactors();
	// seiveWithAllPrimes();
	init();

	int t=1;
	cin>>t;
	for(int i=0;i<t;i++){
		solve(i+1);
	}
	cerr<<"time taken : "<<(float)clock()/CLOCKS_PER_SEC<<" secs"<<endl;
	return 0;
}