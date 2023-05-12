class Solution {
public:
    int fib(int n,int *memo=NULL) {
        if(n==0 || n==1) return n;
        if(!memo) memo=(int *)calloc(n+1,sizeof(int));
        if(memo[n] != 0) return memo[n];
        memo[n]=fib(n-1,memo)+fib(n-2,memo);
        return memo[n];
    }
};