// problem link : https://leetcode.com/problems/repeated-dna-sequences/
// solution : below code

class Solution {
public:
    vector<string> findRepeatedDnaSequences(string s) {
        vs v;
        int n=s.size();
        unordered_map<string,int> mp;
        F(i,0,n-10+1){
            mp[s.substr(i,10)]++;
        }
        FEACH(pr,mp){
            if(pr.second>1) v.pb(pr.first);
        }
        return v;
    }
};
