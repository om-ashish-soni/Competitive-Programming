class ModuloArithmetic{
public:
    static pair<int,int> extended_gcd(int a,int b){
        if(b==0) return{1,1};
        pair<int,int> pr=extended_gcd(b,a%b);
        return {pr.second,pr.first-(a/b)*pr.second};
    }
    static int hcf(int a,int b){
        if(a==0 || b==0) return max(a,b);
        pair<int,int> pr=extended_gcd(a,b);
        return (a*pr.first + b*pr.second);
    }
    static int lcm(int a,int b){
        return (a*b)/(__gcd(a,b));
    }
    static int gcd(int a,int b){
        return __gcd(a,b);
    }
    static int modSub(int a,int b,int mod){
        return ((a%mod - b%mod + mod)%mod);
    }
    static int modMul(int a,int b,int mod){
        return ((a%mod)*(b%mod))%mod;
    }
    static int modAdd(int a,int b,int mod){
        return ((a%mod)+(b%mod))%mod;
    }
    static int modInv(int a,int mod){
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
    static int modDiv(int a,int b,int mod){
        
        a=a%mod;
        int inv=modInv(b,mod);
        int res=(inv*a)%mod;
        return res;
    }
    static int power(long long x, unsigned int y, int p) 
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
     



void printKickStartCase(int t){
    cout<<"Case #"<<t<<": ";
}

class BinarySegmentTree{
public:
    int n=1;
    int sz=1;
    int len=1;
    int offset=0;
    int mod=(1e9)+7;
    vector<int> arr;
    BinarySegmentTree(int n,int mod=MOD1){
        this->n=n;
        this->mod=mod;
        init();
    }
    BinarySegmentTree(vector<int> & v,int mod=MOD1){
        this->n=(int)(v.size());
        this->mod=mod;
        init();
        for(int i=0;i<n;i++){
            if(v[i]==1) this->update(i,1);
        }        
    }
    void init(){
        int l2=log2(n);
        l2++;
        this->len=(1LL<<l2);
        this->offset=len-1;
        this->sz=len+offset;
        this->arr.assign(sz+1,0);
    }
    int stopper=0;
    int getUtil(int sl,int sr,int l,int r,int index){
        if(sr<l || sl>r) return 0;
        if(l<=sl && r>=sr) return arr[index];
        int mid=(sl+sr)/2;
        int left=0,right=0;
        left=getUtil(sl,mid,l,min(mid,r),2*index+1);
        right=getUtil(mid+1,sr,max(l,mid+1),r,2*index+2);
        int base=(r-mid);
        int mult=1;
        if(base>0) mult=ModuloArithmetic::power(2,base,mod);
        left=ModuloArithmetic::modMul(left,mult,mod);
        int key=ModuloArithmetic::modAdd(left,right,mod);
        return key;
    }
    int get(int l,int r){
        int index=0;
        int sl=0;
        int sr=len-1;
        int l_index=l;
        int r_index=r;
        int key=this->getUtil(sl,sr,l_index,r_index,index);
        return key;
    }
    void update(int index,int val){
        index+=offset;
        arr[index]=val;
        int base=1;
        while(index>0){
            index=(index-1)/2;
            int left=arr[2*index+1];
            int right=arr[2*index+2];
            int mult=ModuloArithmetic::power(2,base,mod);
            left=ModuloArithmetic::modMul(left,mult,mod);
            arr[index]=ModuloArithmetic::modAdd(left,right,mod);
            base<<=1;
        }
    }
    void print(){
        for(auto num:arr) cout<<num<<" ";cout<<endl;
    }
    static void how_to_use(){
        int n;
        cin>>n;
        int q;
        cin>>q;
        string s;
        cin>>s;
        vector<int> v(n);
        for(int i=0;i<n;i++){
            if(s[i]=='1') v[i]=1;
            else v[i]=0;
        }
        BinarySegmentTree *bst=new BinarySegmentTree(v);
        for(int i=0;i<q;i++){
            int type;
            cin>>type;
            if(type==1){
                int index;
                cin>>index;
                index--;
                v[index]=(v[index] xor 1);
                bst->update(index,v[index]);
            }else{
                int l,r;
                cin>>l>>r;
                l--;
                r--;
                int ans=bst->get(l,r);
                cout<<ans<<endl;
            }
        }
        delete bst;

    }
};
