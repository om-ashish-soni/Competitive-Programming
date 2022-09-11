// problem link : https://leetcode.com/contest/weekly-contest-310/problems/optimal-partition-of-string/
// solution : below code

class Solution {
public:
    int partitionString(string s) {
        map<char,bool> mp;
        int ctr=1;
        for(auto c:s){
            if(mp.count(c)){
                ctr++;
                mp.clear();
            }
            mp[c]=true;
        }
        return ctr;
    }
};
