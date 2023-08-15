// problem link : https://leetcode.com/problems/repeated-string-match/description/
// solution : below code

class Solution {
public:
    int repeatedStringMatch(string a, string b) {
        int ctr=1;
        string s=a;
        while(s.size()<b.size()){
            s+=a;
            ctr++;
        }
        int overhead=3;
        while(overhead--){
            auto index=s.find(b);
            if(index != string::npos){
                return ctr;
            }
            ctr++;
            s+=a;
        }
        return -1;
    }
};