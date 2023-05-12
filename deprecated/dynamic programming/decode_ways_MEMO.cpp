class Solution {
public:
    int numDecoding(string s,vector<int> &memo,int i=0){
        if(s[i] == '0'){ memo[i]=0; return 0;}
        if(i>=s.size()-1){ return 1;}
        if(memo[i] != -1) return memo[i];
        int num=stoi(s.substr(i,2));
        if(num<=26){ memo[i]=numDecoding(s,memo,i+1)+numDecoding(s,memo,i+2);}
        else{ memo[i]=numDecoding(s,memo,i+1);}
        return memo[i];
    }
    int numDecodings(string s) {
        if(s.size()==1){
            if(s[0]=='0') return 0;
            else return 1;
        }
        vector<int> memo(s.size(),-1);
        numDecoding(s,memo);
        return memo[0];
    }
};