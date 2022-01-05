class Solution {
public:
    int climbStairs1(int n,int memo[]){
        if(n==0) return 0;
        if(0 != memo[n]) return memo[n];
        memo[n]=climbStairs1(n-1,memo)+climbStairs1(n-2,memo);
        return memo[n];
    }
    int climbStairs(int n) {
        int memo[46]={0};
        memo[1]=1;
        memo[2]=2;
        return climbStairs1(n,memo);
    }
};