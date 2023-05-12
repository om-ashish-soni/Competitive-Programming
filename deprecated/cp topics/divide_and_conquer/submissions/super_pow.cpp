// problem link : https://leetcode.com/problems/super-pow/description/
// solution : below code

class Solution {
public:
    long long modAdd(long long a,long long b,long long mod){
        return (a%mod + b%mod)%mod;
    }
    long long modMul(long long a,long long b,long long mod){
        return ((a%mod) * (b%mod))%mod;
    }
    long long power(long long a,long long n,long long mod){
        long long res=1;
        while(n>0){
            // cout<<"n : "<<n<<" , a : "<<a<<endl;
            if((n&1)==1){
                res=modMul(res,a,mod);
            }
            a=modMul(a,a,mod);
            n>>=1;
        }
        return res;
    }
    long long superPow(long long a, vector<int>& b) {
        const long long mod=1337LL;
        long long val=1;
        
        for(auto p:b){
            long long next=power(val,10LL,mod);
            val=next;
            long long curr=power(a,p,mod);
            val=modMul(val,curr,mod);
        }
        return val;
    }
};
