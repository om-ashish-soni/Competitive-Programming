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
class ECCPointEngine{
public:
	int p,a,b;
	ECCPointEngine(int p,int a,int b){
		this->p=p;
		this->a=a;
		this->b=b;
	}
	int fun(int x){
		return modAdd(power(x,3LL,p) , modAdd(modMul(a,x,p) , b , p) , p);
	}
	bool isQR(int a,int p){
		int half=(p-1)/2;
		return power(a,half,p)==1;
	}
	vector<int> getQRSolutions(int a,int p){
		if(isQR(a,p)==false){ 
			return {};
		}
		int first=power(a,(p+1)/4,p);
		int second=modSub(p,first,p);
		return {first,second};
	}
	vector<pair<int,int>> genPoints(){
		int threshold=p;
		vector<pair<int,int>> points;
		int x=0;
		
		while(x<p){
			int a=fun(x);
			vector<int> y_values;
			y_values=getQRSolutions(a,p);
			for(auto y:y_values){
				pair<int,int> curr={x,y};
				points.push_back(curr);
			}
			x++;
		}
		return points;
	}
};
void printPoints(vector<pair<int,int>> & points){
	for(auto & pr:points){
		cout<<"{ "<<pr.first<<" , "<<pr.second<<" } "<<endl;
	}
}
void solve(){
	int p,a,b;
	cin>>p>>a>>b;
	ECCPointEngine *ecc=new ECCPointEngine(p,a,b);
	vector<pair<int,int>> points=ecc->genPoints();
	printPoints(points);
	delete ecc;
}
signed main(){
	solve();
	return 0;
}