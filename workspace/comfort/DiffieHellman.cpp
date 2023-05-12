#include<bits/stdc++.h>
#define int long long
using namespace std;
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
using namespace ModuloArithmetic;
class DiffieHellman{
public:
	int p,g;
	DiffieHellman(int p,int g){
		this->p=p;
		this->g=g;
	}
	pair<int,int> genKey(int x,int y){
		int alice_1=power(g,x,p);
		int bob_1=power(g,y,p);
		int alice_2=power(bob_1,x,p);
		int bob_2=power(alice_1,y,p);
		return {alice_2,bob_2};
	}
};
void solve(){
	int p,g;
	cin>>p>>g;
	DiffieHellman *dh=new DiffieHellman(p,g);
	int x,y;
	cin>>x>>y;

	cout<<"x : "<<x<<endl;
	cout<<"y : "<<y<<endl;
	cout<<"key : "<<power(g,x*y,p)<<endl;

	pair<int,int> keys=dh->genKey(x,y);
	cout<<"alice key : "<<keys.first<<endl;
	cout<<"bob key : "<<keys.second<<endl;
	delete dh;
}
signed main(){
	solve();
	return 0;
}