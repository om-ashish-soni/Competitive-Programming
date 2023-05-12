class Solution {
public:
    int ncr(int n,int r,map<pair<int,int>,int> &memo){
        if(r==0 || r==n) return 1;
        if(memo[{n,r}]) return memo[{n,r}];
        memo[{n,r}]=ncr(n-1,r-1,memo)+ncr(n-1,r,memo);
        return memo[{n,r}];
    }
    vector<int> getRow(int rowIndex) {
        map<pair<int,int>,int> memo;
        vector<int> v;
        for(int i=0;i<=rowIndex;i++){
            v.push_back(ncr(rowIndex,i,memo));
        }
        return v;
    }
};