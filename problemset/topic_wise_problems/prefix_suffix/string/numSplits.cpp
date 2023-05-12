// problem link : https://leetcode.com/problems/number-of-good-ways-to-split-a-string/
// solution : below code

class Solution {
public:
    int numSplits(string s) {
        int n=s.size();
        vector<int> pref(n,0);
        vector<int> suff(n,0);
        unordered_set<char> hash;
        hash.clear();
        for(int i=0;i<n;i++){
            hash.insert(s[i]);
            pref[i]=hash.size();
        }
        hash.clear();
        for(int i=n-1;i>=0;i--){
            hash.insert(s[i]);
            suff[i]=hash.size();
        }
        int ctr=0;
        for(int i=0;i<n-1;i++){
            if(pref[i]==suff[i+1]) ctr++;
        }
        return ctr;
    }
};
