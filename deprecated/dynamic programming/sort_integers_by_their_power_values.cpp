// problem link : https://leetcode.com/problems/sort-integers-by-the-power-value/
// solution : below code

map<int,int> memo;
bool isinit=false;
vector<pair<int,int>> dp(1010);
int getPower(int n){
    if(n<2) return 0;
    if(memo.count(n)) return memo[n];
    int steps=0;
    if(n%2==0) steps=1+getPower(n/2);
    else steps=1+getPower(3*n + 1);
    memo[n]=steps;
    return steps;
}
template <typename T>
vector<T> getSubvector(vector<T>& v,int first,int last){
    vector<T> vector(v.begin()+first,v.begin()+last+1);
    return vector;
}
void init(){
    for(int i=1;i<1010;i++){
        dp[i]={getPower(i),i};
    }
}
class Solution {
public:
    
    int getKth(int lo, int hi, int k) {
        if(isinit==false) init();
        vector<pair<int,int>> v=getSubvector(dp,lo,hi);
        sort(begin(v),end(v));
        return v[k-1].second;
    }
};
