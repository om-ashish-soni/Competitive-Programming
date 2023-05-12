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
    int refine(int a,int p){
        return (a+p)%p;
    }
};
namespace Printer{
    void printPoint(pair<int,int>  pr){
        cout<<"{ "<<pr.first<<" , "<<pr.second<<" } "<<endl;
    }
    void printPoints(vector<pair<int,int>> & points){
    	for(auto & pr:points){
    		printPoint(pr);
    	}
    }
};
using namespace ModuloArithmetic;
using namespace Printer;
class ECCPointEngine{
public:
	int p,a,b,d,r;
	pair<int,int> e1,e2;
	vector<pair<int,int>> curvePoints;
	map<pair<int,int>,char> mp;
	ECCPointEngine(int p,int a,int b,int d,int r,int domain=130){
		this->p=p;
		this->a=a;
		this->b=b;
		this->d=d;
		this->r=r;
		this->curvePoints=genPoints(domain);
		this->e1=curvePoints.back();
		this->e2=scalar_multiply(e1,d);
		cout<<"p : "<<p<<endl;
		cout<<"a : "<<a<<endl;
		cout<<"b : "<<b<<endl;
		cout<<"d : "<<d<<endl;
		cout<<"r : "<<r<<endl;
		cout<<"e1 : ";printPoint(this->e1);
		cout<<"e2 : ";printPoint(this->e2);
		for(int i=0;i<domain;i++){
		    mp[curvePoints[i]]=(char)(i);
		}
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
	// case 1
	pair<int,int> plus(pair<int,int> first,pair<int,int> second){
	    int x1=first.first;
	    int x2=second.first;
	    int y1=first.second;
	    int y2=second.second;
	    int x_d=refine(x1-x2,p);
	    int y_d=refine(y1-y2,p);
	    if(x_d==0){
	        throw "infinite slope";
	    }
	    int slope=modDiv(y_d,x_d,p);
	   // cout<<"slope : "<<slope<<endl;
	    int slope_sq=modMul(slope,slope,p);
	    int cut=modAdd(x1,x2,p);
	    int x3=modSub(slope_sq,cut,p);
	   // cout<<"x3 : "<<x3<<endl;
	    int y3=modSub(modMul(slope,modSub(x1,x3,p),p),y1,p);
	    return {x3,y3};
	}
	// case 2
	pair<int,int> twice(pair<int,int> point){
	    int x1=point.first;
	    int y1=point.second;
	    if(y1==0){
	        throw "y1 is 0";
	    }
	    int slope=modDiv(modAdd(modMul(3LL,modMul(x1,x1,p),p),a,p),modMul(2LL,y1,p),p);
	    int x3=modSub(modMul(slope,slope,p),modMul(2LL,x1,p),p);
	    int y3=modSub(modMul(slope,modSub(x1,x3,p),p),y1,p);
	    return {x3,y3};
	}
	
	pair<int,int> scalar_multiply(pair<int,int> first,int val){
	    int x=first.first;
	    int y=first.second;
	    int len_powers=ceil(log2(val))+1;
	    vector<pair<int,int>> powers(len_powers);
	    powers[0]=first;
	    for(int i=1;i<len_powers;i++){
	        powers[i]=twice(powers[i-1]);
	       // cout<<"i : "<<i<<" => "<<powers[i].first<<" , "<<powers[i].second<<endl;
	    }
	    bool isFirst=true;
	    pair<int,int> result;
	    for(int i=0;i<len_powers;i++){
	        int base=(1LL<<i);
	        
	        if((val&base)){
	           // cout<<val<<" vs "<<base<<" : "<<(val&base)<<endl;    
	            if(isFirst){
	                result=powers[i];
	            }else{
	                result=plus(result,powers[i]);
	            }
	        }
	    }
	   // cout<<result.first<<" , "<<result.second<<endl;
	    return result;
	}
	// case 3
	pair<int,int> negative(pair<int,int> point){
	    return {point.first,modSub(0LL,point.second,p)};
	}
	pair<int,int> subtract(pair<int,int> first,pair<int,int> second){
	    second=negative(second);
	    return plus(first,second);
	}
	vector<pair<int,int>> genPoints(int threshold){
	    vector<pair<int,int>> seeds=genPoints();
	    vector<pair<int,int>> & points=seeds;
	    set<pair<int,int>> pointSet(seeds.begin(),seeds.end());
	    int index=0;
	    
        while(index<threshold){
            int i=index;
            for(int j=0;j<=i;j++){
                try{
	                pair<int,int> plusPoint=plus(points[i],points[j]);    
	                if(pointSet.find(plusPoint)==pointSet.end()){
	                    pointSet.insert(plusPoint);
	                    points.push_back(plusPoint);
	                }
	            }catch(...){}
	            if(points.size()>=threshold){
	                break;
	            }
            }
            if(points.size()>=threshold){
                break;
            }
            index++;
        }
	    return vector<pair<int,int>>(pointSet.begin(),pointSet.end());
	}
	
	vector<pair<int,int>> encrypt(char ch){
	    pair<int,int> m=curvePoints[(int)(ch)];
	    cout<<"plain : ";printPoint(m);
	    pair<int,int> c1=scalar_multiply(e1,r);
	    pair<int,int> c2=plus(m,scalar_multiply(e2,r));
	    cout<<"e1*r : ";printPoint(scalar_multiply(e1,r));
	    cout<<"e2*r : ";printPoint(scalar_multiply(e2,r));
	    cout<<"c1 : ";printPoint(c1);
	    cout<<"c2 : ";printPoint(c2);
	    return {c1,c2};
	}
	char decrypt(vector<pair<int,int>> & cipherText){
	    pair<int,int> c1,c2;
	    c1=cipherText[0];
	    c2=cipherText[1];
	    pair<int,int> decrypted=subtract(c2,scalar_multiply(c1,d));
	    cout<<"decrypted : ";printPoint(decrypted);
	    cout<<"char : "<<mp[decrypted]<<endl;
	    return 'z';
	}
	void show_cases(){
	    cout<<"first case : +++++++++++++++++++++++++++++++++++++++++++++"<<endl;
    
        pair<int,int> first,second;
        first={12,5};
        second={11,11};
        cout<<"first : ";printPoint(first);
        cout<<"second : ";printPoint(second);
        pair<int,int> plusPoint=plus(first,second);
        cout<<"first + second : ";printPoint(plusPoint);
        
        
        cout<<"second case : ********************************************"<<endl;
        pair<int,int> point={1,4};
        cout<<"point : ";printPoint(point);
        pair<int,int> twice_point=twice(point);
        cout<<"twice_point : ";printPoint(twice_point);
        
        cout<<"third case :  ------------------------------------------"<<endl;
        pair<int,int> neg_point=negative(point);
        cout<<"negivate point : ";printPoint(neg_point);
        
	}
	
};

void solve(){
	int p,a,b,d,r;
	cin>>p>>a>>b>>d>>r;
	ECCPointEngine *ecc=new ECCPointEngine(p,a,b,d,r);
	vector<pair<int,int>> points=ecc->genPoints(130);
	// cout<<"\n\ncases : "<<endl;
    // ecc->show_cases();
    // cout<<"\n\nencryption : "<<endl;
    // char ch;
    // cin>>ch;
    // vector<pair<int,int>> cipherText=ecc->encrypt(ch);
    // ecc->decrypt(cipherText);
    pair<int,int> pr=ecc->plus({12,5},{11,11});
    cout<<pr.first<<" , "<<pr.second<<endl;
	delete ecc;
}
signed main(){
	solve();
	return 0;
}