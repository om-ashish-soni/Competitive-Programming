// problem link : https://leetcode.com/problems/concatenation-of-consecutive-binary-numbers/
// solution : below code

bool isinit=false;
vector<ll> dp(1e5 + 10,0);
void init(){
    dp[1]=1;
    F(i,2,1e5+10){
        ll shift=log2(i);
        shift++;
        dp[i]=i;
        ll addon=dp[i-1];
        while(shift--){
            addon=(addon*2)%(MOD1);
        }
        dp[i]=(dp[i]+addon)%(MOD1);
    }
}
class Solution {
public:
    int concatenatedBinary(int n) {
        if(isinit==false) init();
        return dp[n];
    }
};
