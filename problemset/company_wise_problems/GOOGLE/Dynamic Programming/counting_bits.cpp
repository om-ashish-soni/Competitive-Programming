// problem link : https://leetcode.com/problems/counting-bits/
// solution : below code


const int M=1e5 + 10;
vector<int> dp(M,0);
bool isDpDone=false;

int getBits(int num){
    bitset<20> bs(num);
    return bs.count();
}
void countBitsDp(){
    isDpDone=true;
    for(int i=0;i<M;i++){
        dp[i]=getBits(i);
    }
}
class Solution {
public:
    vector<int> countBits(int n) {
        if(isDpDone==false) countBitsDp();
        return vector(dp.begin(),dp.begin()+n+1);
    }
};
