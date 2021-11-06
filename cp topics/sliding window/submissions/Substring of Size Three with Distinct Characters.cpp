// problem Link : https://leetcode.com/problems/substrings-of-size-three-with-distinct-characters/
// Problem type: sliding window

class Solution {
public:
    int countGoodSubstrings(string s) {
        if(s.size()<3) return 0;
        int l,r;
        l=0,r=2;
        int goodStr=0;
        unordered_map<char,int> ump;
        ump[s[0]]++;
        ump[s[1]]++;
        ump[s[2]]++;
        while(r<s.size()){
            if(ump[s[l]]<2 && ump[s[l+1]]<2 && ump[s[l+2]]<2) goodStr++;
            ump[s[l]]--;
            r++;
            l++;
            if(r<s.size()) ump[s[r]]++;
        }
        return goodStr;
    }
};
