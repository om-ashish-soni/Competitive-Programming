// Problem link  : https://practice.geeksforgeeks.org/problems/ncr1019/1
// Solution : below code

// { Driver Code Starts
// Initial Template for C++

#include <bits/stdc++.h>
using namespace std;

 // } Driver Code Ends
// User function Template for C++
#define ll long long
pair<ll,ll> extended_gcd(ll a,ll b){
	if(b==0) return{1,1};
	pair<ll,ll> pr=extended_gcd(b,a%b);
	return {pr.second,pr.first-(a/b)*pr.second};
}
ll modMul(ll a,ll b,ll mod){
    return ((a%mod)*(b%mod))%mod;
}
ll modAdd(ll a,ll b,ll mod){
    return ((a%mod)+(b%mod))%mod;
}
ll modInv(ll a,ll mod){
    ll x,y;
    pair<ll,ll> pr=extended_gcd(a,mod);
    x=pr.first;
    y=pr.second;
    ll g=(a*x + mod*y);
    if(g!=1){
        cerr<<"modular inverse does not exist , gcd != 1"<<endl;
        exit(0);
    }
    // adding m to avoid negative value of x 
    ll res=(x%mod + mod)%mod;
    return res;
}
ll modDiv(ll a,ll b,ll mod){
    
    a=a%mod;
    ll inv=modInv(b,mod);
    ll res=(inv*a)%mod;
    return res;
}

class NCR{
	public : 
	ll mod=-1;
	ll n,r,res=1;
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
	NCR(ll n,ll r):n(n),r(r){
		if(r>n-r) r=n-r;
		this->computeNcr();
	}
	NCR(ll n,ll r,ll mod):n(n),r(r),mod(mod){
	    
		if(r>n-r) r=n-r;
		this->computeNcrMod();
	}
	ll get(){
		return res;
	}
};
class Solution{
public:


    int nCr(int n, int r){
        ll mod(1e9+7);
        NCR ncr=*new NCR(n,r,mod);
        return (ll)ncr.get();
    }
};

// { Driver Code Starts.

int main(){
    int t;
    cin>>t;
    while(t--){
        int n, r;
        cin>>n>>r;
        
        Solution ob;
        cout<<ob.nCr(n, r)<<endl;
    }
    return 0;
}  // } Driver Code Ends
